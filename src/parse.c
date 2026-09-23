/* parse.c - 按 Ecliptica 世界真实日志格式解析战斗事件
 *
 * 做法：对日志消息体做**固定句式前缀匹配**，全部句式取自真实 output_log，
 * 解析器本身不保存任何状态（世界判定交给 stats.c），因此既好测试，也天然
 * 支持把同一份日志回放给工具做回归。
 */
#include "parse.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- 小工具 ---------------- */

static bool starts(const char* s, const char* lit)
{
    return strncmp(s, lit, strlen(lit)) == 0;
}

static bool ci_starts(const char* s, const char* lit)
{
    while (*lit) {
        if (tolower((unsigned char)*s) != tolower((unsigned char)*lit)) return false;
        s++; lit++;
    }
    return true;
}

/* 把 [s, s+n) 拷进 dst（去掉首尾空白） */
static void copy_span(char* dst, int cap, const char* s, size_t n)
{
    if (cap <= 0) return;
    while (n > 0 && (*s == ' ' || *s == '\t')) { s++; n--; }
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' ||
                     s[n - 1] == '\r' || s[n - 1] == '\n')) n--;
    if ((int)n > cap - 1) n = (size_t)(cap - 1);
    memcpy(dst, s, n);
    dst[n] = 0;
}

/* 取 [s, term) 区间（term 为 NULL 时取到串尾），再 trim */
static void copy_until(char* dst, int cap, const char* s, const char* term)
{
    const char* e = term ? term : (s + strlen(s));
    copy_span(dst, cap, s, (size_t)(e - s));
}

static const char* trim_left(const char* s)
{
    while (*s == ' ' || *s == '\t') s++;
    return s;
}

/* 去掉行尾 \r\n 的临时副本（最多 1024 字节） */
static void rtrim_inplace(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\r' || s[n - 1] == '\n' ||
                     s[n - 1] == ' ' || s[n - 1] == '\t')) s[--n] = 0;
}

/* ---------------- 时间戳 ---------------- */

/* Howard Hinnant days_from_civil：返回 1970-01-01 起的天数 */
static long days_from_civil(int y, int m, int d)
{
    y -= (m <= 2);
    long era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = (unsigned)(y - era * 400);
    unsigned doy = (unsigned)((153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1);
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097L + (long)doe - 719468L;
}

double parse_timestamp(const char* raw)
{
    if (!raw) return 0;
    const char* p = raw;
    while (*p == ' ' || *p == '\t') p++;
    if (strlen(p) < 19) return 0;
    if (p[4] != '.' || p[7] != '.' || p[10] != ' ' || p[13] != ':' || p[16] != ':')
        return 0;
    static const int pos[6] = { 0, 5, 8, 11, 14, 17 };
    for (int i = 0; i < 6; i++) {
        if (!isdigit((unsigned char)p[pos[i]]) || !isdigit((unsigned char)p[pos[i] + 1]))
            return 0;
    }
    int y  = (p[0] - '0') * 10 + (p[1] - '0');
    y = y * 100 + (p[2] - '0') * 10 + (p[3] - '0');
    int mo = (p[5] - '0') * 10 + (p[6] - '0');
    int d  = (p[8] - '0') * 10 + (p[9] - '0');
    int h  = (p[11] - '0') * 10 + (p[12] - '0');
    int mi = (p[14] - '0') * 10 + (p[15] - '0');
    int sec = (p[17] - '0') * 10 + (p[18] - '0');
    if (mo < 1 || mo > 12 || d < 1 || d > 31) return 0;
    if (h > 23 || mi > 59 || sec > 60) return 0;
    long days = days_from_civil(y, mo, d);
    return (double)days * 86400.0 + h * 3600.0 + mi * 60.0 + sec;
}

/* ---------------- 消息体定位 ---------------- */

/* 校验 "YYYY.MM.DD HH:MM:SS"（19 字符），并把 msg 指向 "- " 之后的正文 */
static bool split_line(const char* raw, const char** msg)
{
    static const char digits[19] = "0000.00.00 00:00:00";
    for (int i = 0; i < 19; i++) {
        char c = raw[i];
        if (!c) return false;
        if (digits[i] == '.') { if (c != '.') return false; }
        else if (digits[i] == ' ') { if (c != ' ') return false; }
        else if (digits[i] == ':') { if (c != ':') return false; }
        else if (c < '0' || c > '9') return false;
    }
    const char* p = strchr(raw + 19, '-');
    if (!p) return false;
    p++;
    while (*p == ' ') p++;
    *msg = p;
    return true;
}

/* ---------------- 数值 ---------------- */

static bool parse_u64(const char* s, double* out)
{
    s = trim_left(s);
    if (!isdigit((unsigned char)*s)) return false;
    char* end = NULL;
    double v = strtod(s, &end);
    if (end == s) return false;
    *out = v;
    return true;
}

static bool parse_f32(const char* s, double* out)
{
    s = trim_left(s);
    char* end = NULL;
    double v = strtod(s, &end);
    if (end == s) return false;
    *out = v;
    return true;
}

/* 去掉 Udon 克隆后缀 "(Clone)" 与尾部空格 */
static void strip_clone(char* s)
{
    char* c = strstr(s, "(Clone)");
    if (!c) return;
    size_t n = (size_t)(c - s);
    while (n > 0 && s[n - 1] == ' ') n--;
    s[n] = 0;
}

/* ---------------- 事件识别 ---------------- */

static bool parse_msg(const char* m, Event* ev)
{
    /* ownership of <对象> transferred to <玩家> —— 目标（仇恨）切换 */
    if (starts(m, "ownership of ")) {
        const char* rest = m + strlen("ownership of ");
        const char* sep = strstr(rest, " transferred to ");
        if (!sep) return false;
        copy_until(ev->name, EV_NAME_CAP, rest, sep);
        strip_clone(ev->name);                       /* "Amaziah(Clone)" -> "Amaziah" */
        copy_until(ev->cls, EV_CLASS_CAP, sep + strlen(" transferred to "), NULL);
        if (!ev->cls[0]) return false;               /* 目标为空 -> 参考实现同样丢弃 */
        ev->type = EV_OWNERSHIP;
        return true;
    }

    /* Dealing <n> STRIKE damage / Dealing <n> NON-STRIKE damage */
    if (starts(m, "Dealing ")) {
        const char* rest = m + strlen("Dealing ");
        const char* sp = strchr(rest, ' ');
        if (!sp) return false;
        double n = 0;
        if (!parse_u64(rest, &n)) return false;
        const char* kind = trim_left(sp);
        bool strike;
        if (starts(kind, "STRIKE damage")) strike = true;
        else if (starts(kind, "NON-STRIKE damage")) strike = false;
        else return false;                            /* 例如 MAGIC damage 直接忽略 */
        ev->type = EV_DEALT;
        ev->amount = n;
        ev->flag = strike;
        return true;
    }

    /* damage has been taken: <n>, from source: <src> */
    if (starts(m, "damage has been taken: ")) {
        const char* rest = m + strlen("damage has been taken: ");
        const char* sep = strstr(rest, ", from source:");
        if (!sep) {
            double n = 0;
            if (!parse_u64(rest, &n)) return false;
            ev->type = EV_DAMAGE_TAKEN;
            ev->amount = n;
            ev->name[0] = 0;
            return true;
        }
        double n = 0;
        char numbuf[32];
        copy_until(numbuf, sizeof(numbuf), rest, sep);
        if (!parse_u64(numbuf, &n)) return false;
        copy_until(ev->name, EV_NAME_CAP, sep + strlen(", from source:"), NULL);
        ev->type = EV_DAMAGE_TAKEN;
        ev->amount = n;
        return true;
    }

    /* ECLIPTICA - now ... */
    if (ci_starts(m, "ECLIPTICA - now ")) {
        const char* rest = m + strlen("ECLIPTICA - now ");
        if (starts(rest, "fighting boss: ")) {
            const char* s = rest + strlen("fighting boss: ");
            const char* end = strstr(s, " on phase: ");
            if (!end) end = s + strlen(s);
            copy_until(ev->name, EV_NAME_CAP, s, end);
            /* 去掉 Udon 克隆后缀 (Clone) */
            size_t n = strlen(ev->name);
            const char* clone = strstr(ev->name, "(Clone)");
            if (clone) { n = (size_t)(clone - ev->name); while (n > 0 && ev->name[n-1] == ' ') n--; ev->name[n] = 0; }
            if (!ev->name[0]) return false;
            const char* ph = strstr(s, " on phase: ");
            if (ph) parse_f32(ph + strlen(" on phase: "), &ev->progress);
            ev->type = EV_BOSS_FIGHT;
            return true;
        }
        if (starts(rest, "in stage: ")) {
            const char* s = rest + strlen("in stage: ");
            const char* end = strstr(s, " on phase: ");
            if (!end) end = s + strlen(s);
            copy_until(ev->name, EV_NAME_CAP, s, end);
            if (starts(ev->name, "Stage_")) memmove(ev->name, ev->name + 6, strlen(ev->name + 6) + 1);
            if (!ev->name[0]) return false;
            const char* ph = strstr(s, " on phase: ");
            if (ph) parse_f32(ph + strlen(" on phase: "), &ev->progress);
            const char* cl = strstr(s, " as class: ");
            if (cl) copy_until(ev->cls, EV_CLASS_CAP, cl + strlen(" as class: "), NULL);
            ev->type = EV_STAGE;
            return true;
        }
        if (starts(rest, "in intermission")) { ev->type = EV_INTERMISSION; return true; }
        if (starts(rest, "in lobby"))        { ev->type = EV_LOBBY;        return true; }
        return false;
    }

    /* Boss <名字> dead, personal damage dealt: */
    if (starts(m, "Boss ")) {
        const char* rest = m + strlen("Boss ");
        const char* sep = strstr(rest, " dead, personal damage dealt:");
        if (!sep) return false;
        copy_until(ev->name, EV_NAME_CAP, rest, sep);
        if (!ev->name[0]) return false;
        ev->type = EV_BOSS_DEAD;
        return true;
    }

    /* STRIKE DMG: n / NON-STRIKE DMG: n */
    if (starts(m, "STRIKE DMG: ")) {
        if (!parse_u64(m + strlen("STRIKE DMG: "), &ev->amount)) return false;
        ev->type = EV_STRIKE_TOTAL;
        return true;
    }
    if (starts(m, "NON-STRIKE DMG: ")) {
        if (!parse_u64(m + strlen("NON-STRIKE DMG: "), &ev->amount)) return false;
        ev->type = EV_NON_STRIKE_TOTAL;
        return true;
    }

    /* 房间进出 */
    if (starts(m, "[Behaviour] Entering Room: ")) {
        copy_until(ev->name, EV_NAME_CAP, m + strlen("[Behaviour] Entering Room: "), NULL);
        ev->type = EV_ROOM_ENTER;
        return true;
    }
    if (starts(m, "[Behaviour] Joining wrld_")) {
        copy_until(ev->name, EV_NAME_CAP, m + strlen("[Behaviour] Joining "), NULL);
        ev->type = EV_ROOM_JOIN;
        return true;
    }

    /* 会话存档（= 阶段内拾取印记） */
    if (ci_starts(m, "ECLIPTICA saving SESSION ID")) {
        parse_u64(m + strlen("ECLIPTICA saving SESSION ID"), &ev->amount);
        ev->type = EV_SESSION_SAVE;
        return true;
    }

    /* 令牌 */
    if (starts(m, "spawn token, ")) {
        const char* rest = m + strlen("spawn token, ");
        const char* sep = strstr(rest, ", ");
        if (!sep) return false;
        char runebuf[16];
        copy_until(runebuf, sizeof(runebuf), rest, sep);
        if (!strcmp(runebuf, "True")) ev->flag = true;
        else if (!strcmp(runebuf, "False")) ev->flag = false;
        else return false;
        parse_u64(sep + 2, &ev->amount);
        ev->type = EV_TOKEN_SPAWN;
        return true;
    }

    /* 敌人工池 */
    if (starts(m, "Initializing Enemy POOL ID")) {
        const char* rest = m + strlen("Initializing Enemy POOL ID");
        const char* sep = strstr(rest, " as ENEMY ID ");
        if (!sep) return false;
        double slot = 0, kind = 0;
        char buf[24];
        copy_until(buf, sizeof(buf), rest, sep);
        if (!parse_u64(buf, &slot)) return false;
        if (!parse_u64(sep + strlen(" as ENEMY ID "), &kind)) return false;
        ev->slot = (int)slot;
        ev->kind = (int)kind;
        ev->type = EV_ENEMY_SPAWN;
        return true;
    }
    if (starts(m, "Retiring Enemy POOL ID")) {
        double slot = 0;
        if (!parse_u64(m + strlen("Retiring Enemy POOL ID"), &slot)) return false;
        ev->slot = (int)slot;
        ev->type = EV_ENEMY_RETIRE;
        return true;
    }
    if (starts(m, "[Behaviour] No targets to encode on ")) {
        const char* s = m + strlen("[Behaviour] No targets to encode on ");
        copy_until(ev->name, EV_NAME_CAP, s, NULL);
        size_t n = strlen(ev->name);
        if (n > 7 && !strcmp(ev->name + n - 7, "(Clone)")) ev->name[n - 7] = 0;
        if (!ev->name[0]) return false;
        ev->type = EV_ENEMY_NAME;
        return true;
    }

    return false;
}

/* ---------------- 对外接口 ---------------- */

bool parse_line(const char* raw, Event* out)
{
    memset(out, 0, sizeof(*out));
    out->type = EV_NONE;
    if (!raw || !*raw) return false;

    const char* m = NULL;
    if (!split_line(raw, &m)) {
        /* 少数行带前导空格或没有时间戳；仍尝试直接识别正文 */
        const char* p = trim_left(raw);
        if (!*p) return false;
        if (!parse_msg(p, out)) out->type = EV_NONE;
    } else if (!parse_msg(m, out)) {
        out->type = EV_NONE;                 /* 交给下面按整行判定的分支 */
    }

    out->t = parse_timestamp(raw);

    /* 行尾判定类事件（OnLeftRoom / 退出 / 死亡）：与整条正文精确比对 */
    if (out->type == EV_NONE) {
        const char* body = m ? m : trim_left(raw);
        char b[256];
        copy_span(b, sizeof(b), body, strlen(body));
        rtrim_inplace(b);
        if (!strcmp(b, "[Behaviour] OnLeftRoom") ||
            starts(b, "VRCApplication: HandleApplicationQuit")) {
            out->type = EV_ROOM_LEFT;
        } else if (!strcmp(b, "Local controller dead, switching off.")) {
            out->type = EV_PLAYER_DEAD;
        }
    }
    return out->type != EV_NONE;
}

const char* ev_type_name(EventType t)
{
    switch (t) {
    case EV_NONE:             return "none";
    case EV_ROOM_ENTER:       return "room_enter";
    case EV_ROOM_JOIN:        return "room_join";
    case EV_ROOM_LEFT:        return "room_left";
    case EV_RUN_START:        return "run_start";
    case EV_RUN_END:          return "run_end";
    case EV_STAGE:            return "stage";
    case EV_INTERMISSION:     return "intermission";
    case EV_LOBBY:            return "lobby";
    case EV_BOSS_FIGHT:       return "boss_fight";
    case EV_BOSS_DEAD:        return "boss_dead";
    case EV_STRIKE_TOTAL:     return "strike_total";
    case EV_NON_STRIKE_TOTAL: return "non_strike_total";
    case EV_DEALT:            return "dealt";
    case EV_DAMAGE_TAKEN:     return "damage_taken";
    case EV_OWNERSHIP:        return "ownership";
    case EV_PLAYER_DEAD:      return "player_dead";
    case EV_TOKEN_SPAWN:      return "token_spawn";
    case EV_SESSION_SAVE:     return "session_save";
    case EV_ENEMY_SPAWN:      return "enemy_spawn";
    case EV_ENEMY_RETIRE:     return "enemy_retire";
    case EV_ENEMY_NAME:       return "enemy_name";
    }
    return "?";
}
