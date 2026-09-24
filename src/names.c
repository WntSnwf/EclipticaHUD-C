/* names.c - 名称映射与伤害来源文本美化 */
#include "names.h"
#include "compat.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct { const char* in; const char* out; } Map;

static const Map BOSSES[] = {
    { "DarkMouth",       "Darkmouth" },
    { "FlyLord",         "Beelzebub" },
    { "Nan",             "NaN" },
    { "BuffNoob",        "Buff Noob" },
    { "QueenBug",        "Vesra" },
    { "Gravetender",     "The Gravetender" },
    { "BlackLily",       "The Black Lily" },
    { "Melon",           "Melgor Johnson" },
    { "JackedPumpkin",   "Jacked O' Lantern" },
    { "M41D",            "M-41-D" },
    { "ConeHead",        "Cone Head" },
    { "GoldenGrouch",    "Golden Grouch" },
    { "AntKing",         "Khepri" },
    { "Oone",            "O-One" },
    { "NeoPilot",        "Neo Pilot" },
    { "JimBringer",      "Jim C. Bringer" },
    { "Obisidus",        "Irides" },
    { "ManalyteAncient", "Abaddon" },
};

static const Map STAGES[] = {
    { "BalboaRuins", "Balboa Ruins" },
    { "Bringer",     "Bringer's Desert" },
    { "CopiedCity",  "Copied City" },
    { "GMBigcity",   "GM_BigCity" },
    { "GMFuncFlat",  "GM_Func_Flat" },
    { "LostElysia",  "Lost Elysia" },
    { "ProtoColony", "Proto Colony" },
    { "VRCHub",      "VRChat Hub" },
};

static const char* lookup(const Map* m, int n, const char* in)
{
    if (!in || !*in) return in;
    for (int i = 0; i < n; i++)
        if (!strcmp(m[i].in, in)) return m[i].out;
    return in;
}

const char* boss_display(const char* internal)
{
    return lookup(BOSSES, (int)(sizeof(BOSSES) / sizeof(BOSSES[0])), internal);
}

const char* stage_display(const char* internal)
{
    return lookup(STAGES, (int)(sizeof(STAGES) / sizeof(STAGES[0])), internal);
}

void boss_label(const char* internal, char* out, int cap)
{
    char base[64];
    if (cap <= 0) return;
    boss_base(internal, base, sizeof(base));
    int ph = boss_phase_no(internal);
    if (ph > 1) snprintf_(out, (size_t)cap, "%s (P%d)", boss_display(base), ph);
    else snprintf_(out, (size_t)cap, "%s", boss_display(base));
}

const char* phase_display(double p)
{
    if (p < 0.2) return "Primal";
    if (p < 0.4) return "Penumbral";
    if (p < 0.6) return "Antumbral";
    if (p < 0.8) return "Umbral";
    if (p < 1.0) return "Eclipse";
    return "Eye of the Eclipse";
}

/* ---------------- 名称拆分 ---------------- */

void boss_base(const char* name, char* out, int cap)
{
    char tmp[96];
    if (cap <= 0) return;
    if (!name) name = "";

    /* 先去掉 Udon 克隆后缀，再处理 Phase 形态后缀 */
    strncpy(tmp, name, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = 0;
    char* clone = strstr(tmp, "(Clone)");
    if (clone) {
        char* e = clone;
        while (e > tmp && e[-1] == ' ') e--;
        *e = 0;
    }

    const char* pos = NULL;
    for (const char* p = tmp; (p = strstr(p, "Phase")) != NULL; p++) pos = p;
    if (pos && pos > tmp) {
        const char* d = pos + 5;
        if (*d) {
            int all_digit = 1;
            for (const char* q = d; *q; q++)
                if (!isdigit((unsigned char)*q)) { all_digit = 0; break; }
            if (all_digit) {
                size_t n = (size_t)(pos - tmp);
                if ((int)n > cap - 1) n = (size_t)(cap - 1);
                memcpy(out, tmp, n);
                out[n] = 0;
                return;
            }
        }
    }
    strncpy(out, tmp, (size_t)cap - 1);
    out[cap - 1] = 0;
}

int boss_phase_no(const char* name)
{
    char base[64];
    boss_base(name, base, sizeof(base));
    if (!strcmp(base, name)) return 1;
    const char* pos = NULL;
    for (const char* p = name; (p = strstr(p, "Phase")) != NULL; p++) pos = p;
    if (!pos) return 1;
    int n = atoi(pos + 5);
    return n > 0 ? n : 1;
}

int is_player_summon(const char* name)
{
    if (!name || strncmp(name, "Neko", 4) != 0) return 0;
    const char* d = name + 4;
    if (!*d) return 0;
    for (; *d; d++) if (!isdigit((unsigned char)*d)) return 0;
    return 1;
}

/* ---------------- Ecliptica 系世界识别 ---------------- */

#define ALIAS_MAX 16
#define ALIAS_LEN 64

static char g_alias[ALIAS_MAX][ALIAS_LEN];
static int  g_alias_n = 0;
static bool g_alias_ready = false;

static void alias_add(const char* s)
{
    if (!s || !*s || g_alias_n >= ALIAS_MAX) return;
    if (strlen(s) >= ALIAS_LEN) return;
    for (int i = 0; i < g_alias_n; i++)
        if (!strcmp(g_alias[i], s)) return;
    strcpy(g_alias[g_alias_n], s);
    g_alias_n++;
}

/* 大小写不敏感（仅 ASCII）子串匹配；UTF-8 多字节按字节精确比对 */
static bool ci_contains(const char* hay, const char* needle)
{
    size_t nl = strlen(needle);
    if (!nl) return false;
    for (; *hay; hay++) {
        size_t i = 0;
        while (i < nl && hay[i]) {
            char a = hay[i], b = needle[i];
            if (a >= 'A' && a <= 'Z') a = (char)(a - 'A' + 'a');
            if (b >= 'A' && b <= 'Z') b = (char)(b - 'A' + 'a');
            if (a != b) break;
            i++;
        }
        if (i == nl) return true;
    }
    return false;
}

void names_set_world_aliases(const char* extra)
{
    g_alias_n = 0;
    alias_add("ecliptica");              /* 官方世界名 */

    if (extra && *extra) {
        char buf[192];
        strncpy(buf, extra, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = 0;
        char* p = buf;
        while (*p) {
            char* sep = p;
            while (*sep && *sep != '|' && *sep != ',' && *sep != ';') sep++;
            char save = *sep;
            *sep = 0;
            char* s = p;
            while (*s == ' ' || *s == '\t') s++;
            char* e = s + strlen(s);
            while (e > s && (e[-1] == ' ' || e[-1] == '\t')) *--e = 0;
            alias_add(s);
            if (!save) break;
            p = sep + 1;
        }
    }
    g_alias_ready = true;
}

bool names_is_ecl_world(const char* room_name)
{
    if (!room_name || !*room_name) return false;
    if (!g_alias_ready) names_set_world_aliases(NULL);
    for (int i = 0; i < g_alias_n; i++)
        if (ci_contains(room_name, g_alias[i])) return true;
    return false;
}

/* ---------------- 伤害来源美化 ---------------- */

static void rtrim(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' ||
                     s[n - 1] == '\r' || s[n - 1] == '\n')) s[--n] = 0;
}

/* 拆 "(Khepri) attack_Claws2" -> who = "Khepri"，返回攻击名起点 */
static const char* split_source(const char* s, char* who, int wcap)
{
    if (wcap > 0) who[0] = 0;
    while (*s == ' ') s++;
    if (*s == '(') {
        const char* close = strrchr(s + 1, ')');
        if (close) {
            size_t n = (size_t)(close - (s + 1));
            if ((int)n > wcap - 1) n = (size_t)(wcap - 1);
            if (wcap > 0) { memcpy(who, s + 1, n); who[n] = 0; rtrim(who); }
            s = close + 1;
        }
    }
    while (*s == ' ') s++;
    return s;
}

/* "_" 断开 + 驼峰/数字边界分词，词首大写 */
static void prettify(const char* s, char* out, int cap)
{
    int oi = 0;
    char prev = 0;
    if (cap <= 0) return;
    for (const char* p = s; *p && oi < cap - 1; p++) {
        char c = *p;
        if (c == '_') {
            if (oi > 0 && out[oi - 1] != ' ') out[oi++] = ' ';
            prev = ' ';
            continue;
        }
        int boundary =
            (isupper((unsigned char)c) && islower((unsigned char)prev)) ||
            (isdigit((unsigned char)c) && !isdigit((unsigned char)prev) && prev != ' ' && prev != 0) ||
            (isalpha((unsigned char)c) && isdigit((unsigned char)prev));
        if (boundary && oi > 0 && out[oi - 1] != ' ') out[oi++] = ' ';
        if (oi == 0 || out[oi - 1] == ' ') c = (char)toupper((unsigned char)c);
        out[oi++] = c;
        prev = *p;
    }
    while (oi > 0 && out[oi - 1] == ' ') oi--;
    out[oi] = 0;
}

void source_display(const char* source, char* who, int who_cap, char* attack, int atk_cap)
{
    if (atk_cap <= 0) return;
    attack[0] = 0;
    const char* atk = split_source(source ? source : "", who, who_cap);

    char raw[160];
    strncpy(raw, atk, sizeof(raw) - 1);
    raw[sizeof(raw) - 1] = 0;
    rtrim(raw);

    /* 提取 " (BIG)" / " (13)" 这类后缀：非纯数字才保留 */
    char suffix[48];
    suffix[0] = 0;
    size_t bl = strlen(raw);
    if (bl > 1 && raw[bl - 1] == ')') {
        char* open = strrchr(raw, '(');
        if (open && open > raw && open[-1] == ' ') {
            size_t n = bl - (size_t)(open - raw) - 2;
            int keep = 0;
            if (n < 47) {
                char inner[48];
                memcpy(inner, open + 1, n);
                inner[n] = 0;
                int digits = inner[0] != 0;
                for (char* q = inner; *q; q++)
                    if (!isdigit((unsigned char)*q)) { digits = 0; break; }
                if (!digits) {
                    keep = 1;
                    char low[48];
                    size_t i = 0;
                    for (; inner[i] && i < sizeof(low) - 1; i++)
                        low[i] = (char)tolower((unsigned char)inner[i]);
                    low[i] = 0;
                    snprintf_(suffix, sizeof(suffix), " (%s)", low);
                }
            }
            (void)keep;
            open[-1] = 0;                  /* 无论是否保留后缀，都要去掉括号部分 */
        }
    }

    const char* s = raw;
    if (strncmp(s, "attack_", 7) == 0) s += 7;
    size_t n = strlen(s);
    if (n > 4 && !strcmp(s + n - 4, "_VFX")) n -= 4;
    else if (n > 6 && !strcmp(s + n - 6, "Hitbox")) n -= 6;
    else if (n > 6 && !strcmp(s + n - 6, "Damage")) n -= 6;
    if ((int)n >= (int)sizeof(raw)) n = sizeof(raw) - 1;
    char trimmed[160];
    memcpy(trimmed, s, n);
    trimmed[n] = 0;
    rtrim(trimmed);

    if (!trimmed[0]) {
        snprintf_(attack, (size_t)atk_cap, "hit");
    } else {
        char pretty[128];
        prettify(trimmed, pretty, sizeof(pretty));
        snprintf_(attack, (size_t)atk_cap, "%s%s", pretty, suffix);
    }

    if (!who[0]) {
        strncpy(who, "enemy", (size_t)who_cap - 1);
        who[who_cap - 1] = 0;
    } else if (strncmp(who, "[Missing Key \"", 14) == 0) {
        char key[64];
        strncpy(key, who + 14, sizeof(key) - 1);
        key[sizeof(key) - 1] = 0;
        size_t kl = strlen(key);
        if (kl >= 2 && key[kl - 1] == ']' && key[kl - 2] == '"') key[kl - 2] = 0;
        if (strncmp(key, "e_", 2) == 0) memmove(key, key + 2, strlen(key + 2) + 1);
        if (!strcmp(key, "VirtueBeam")) { strncpy(key, "Black Virtue", sizeof(key) - 1); key[sizeof(key) - 1] = 0; }
        else if (!strcmp(key, "GravetenderOrb")) { strncpy(key, "Gravetender Orb", sizeof(key) - 1); key[sizeof(key) - 1] = 0; }
        prettify(key, who, who_cap);
    }
}
