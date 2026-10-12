/* res.c - 弱点 / 抗性表的解析与查询 */
#include "res.h"
#include "uitext.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 面板上的显示名（按语言，见 uitext_*.h）*/
static const char* const ELEM_DISPLAY[ELEM_COUNT] = TXT_ELEM_DISPLAY;

/* 数据文件里的规范英文键 */
static const char* const ELEM_KEY[ELEM_COUNT] = {
    "Physical", "Fire", "Frost", "Electric", "Luminous", "Shadow", "Poison"
};

/* 数据文件里额外接受的别名（英文规范键之外）。
 * 中文键和日文键都收，**与界面语言无关** —— 三种语言的 exe 认同一套键，
 * 所以同一份数据文件谁都能用。
 * 注意日文和中文写法不同的那几个（氷/電/電気/闇）必须单独列出来，
 * 否则日文用户照着面板上的字写进数据文件反而解析不了。*/
static const char* const ELEM_ALIAS[ELEM_COUNT][5] = {
    { "物", "物理", NULL,       NULL },       /* Physical   中文/日文同形 */
    { "火", "火焰", NULL,       NULL },       /* Fire       中文/日文同形 */
    { "冰", "冰霜", "氷",       NULL },       /* Frost      日文用「氷」   */
    { "电", "雷",   "電",       "電気" },     /* Electric   日文用「電気」 */
    { "光", "圣",   NULL,       NULL },       /* Luminous   中文/日文同形 */
    { "暗", "暗影", "闇",       NULL },       /* Shadow     日文用「闇」   */
    { "毒", "毒素", NULL,       NULL },       /* Poison     中文/日文同形 */
};

const char* res_elem_name(int elem)
{
    if (elem < 0 || elem >= ELEM_COUNT) return "?";
    return ELEM_DISPLAY[elem];
}

const char* res_elem_key(int elem)
{
    if (elem < 0 || elem >= ELEM_COUNT) return "?";
    return ELEM_KEY[elem];
}

/* ---- Boss 内部名 -> 显示名（与本体 names.c 的 BOSSES 表一致）---- */
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

const char* res_boss_display(const char* internal)
{
    if (!internal || !*internal) return internal;
    for (size_t i = 0; i < sizeof(BOSSES) / sizeof(BOSSES[0]); i++)
        if (!strcmp(BOSSES[i].in, internal)) return BOSSES[i].out;
    return internal;                       /* 未收录：表里本来就写内部名 */
}

/* ---- 小工具 ---- */

static char* rtrim(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' ||
                     s[n - 1] == '\r' || s[n - 1] == '\n')) s[--n] = 0;
    return s;
}

static char* ltrim(char* s)
{
    while (*s == ' ' || *s == '\t') s++;
    return s;
}

static int ci_equal(const char* a, const char* b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == 0 && *b == 0;
}

void res_boss_base(const char* name, char* out, int cap)
{
    if (!name) { if (cap > 0) out[0] = 0; return; }
    char tmp[96];
    snprintf(tmp, sizeof(tmp), "%s", name);

    /* 去掉 (Clone) */
    char* clone = strstr(tmp, "(Clone)");
    if (clone) memmove(clone, clone + 7, strlen(clone + 7) + 1);

    /* 去掉结尾的 PhaseN（只认"Phase + 全数字"） */
    char* pos = NULL;
    for (char* p = tmp; (p = strstr(p, "Phase")) != NULL; p++) pos = p;
    if (pos && pos > tmp) {
        const char* d = pos + 5;
        int all_digit = *d != 0;
        for (const char* q = d; *q; q++)
            if (!isdigit((unsigned char)*q)) { all_digit = 0; break; }
        if (all_digit) *pos = 0;
    }
    rtrim(tmp);
    snprintf(out, (size_t)cap, "%s", tmp);
}

int res_boss_phase(const char* name)
{
    if (!name) return 1;
    const char* pos = NULL;
    for (const char* p = name; (p = strstr(p, "Phase")) != NULL; p++) pos = p;
    if (!pos) return 1;
    const char* d = pos + 5;
    /* 只要求 "Phase" 后面紧跟数字；后面的 "(Clone)" 之类照旧忽略。
     * 日志里送的正是 "YukiPhase2(Clone)" 这种形式，早先要求"后面全是数字"
     * 会把形态号一律误判成 1。*/
    if (!isdigit((unsigned char)*d)) return 1;
    return atoi(d);
}

int res_verdict(double mult)
{
    if (mult > 1.0001) return 1;
    if (mult < 0.9999) return -1;
    return 0;
}

/* ---- 解析 ---- */

/* 数据文件里的键 -> 元素序号。英文规范键 + 中文/日文别名都认。 */
static int elem_index(const char* key)
{
    for (int i = 0; i < ELEM_COUNT; i++) {
        if (ci_equal(key, ELEM_KEY[i])) return i;
        for (int k = 0; k < 5 && ELEM_ALIAS[i][k]; k++)
            if (ci_equal(key, ELEM_ALIAS[i][k])) return i;
    }
    return -1;
}

/* 解析 "1.25x" / "1x" / "0.75x" / "1+x (weak)" / "1-x (resist)"
 * 返回 true 表示认出来了。 */
static bool parse_value(const char* val, ElemVal* out)
{
    char buf[96];
    snprintf(buf, sizeof(buf), "%s", val);

    /* 符号写法：1+x (weak) / 1-x (resist) */
    if (strstr(buf, "(weak)"))   { out->kind = VAL_WEAK;   return true; }
    if (strstr(buf, "(resist)")) { out->kind = VAL_RESIST; return true; }

    /* 数值写法：<数字>x */
    char* p = buf;
    char* end = NULL;
    double d = strtod(p, &end);
    if (end == p) return false;                 /* 开头就不是数字 */
    while (*end == ' ') end++;
    if (*end != 'x' && *end != 'X') return false;
    out->kind = VAL_NUM;
    out->mult = d;
    return true;
}

/* 说明行的语言前缀："zh: …" / "en: …" / "ja: …"（前缀必须小写）。
 * 命中则返回标签，*text 指向正文；没命中返回 NULL。
 * 用途：一份数据文件里可以同时写三种语言的说明，各语言版只取自己那份，
 * 数值部分则完全共用。 */
static const char* note_tag(const char* s, const char** text)
{
    static const char* const TAGS[3] = { "zh", "en", "ja" };
    for (int i = 0; i < 3; i++) {
        size_t n = strlen(TAGS[i]);
        if (strncmp(s, TAGS[i], n) != 0) continue;
        if (s[n] != ':') continue;
        const char* r = s + n + 1;
        while (*r == ' ' || *r == '\t') r++;
        *text = r;
        return TAGS[i];
    }
    return NULL;
}

/* 这一段是否已经有数值了（用来判断"这一行是说明还是下一个 Boss 名"）*/
static bool table_started(const BossRes* b)
{
    if (b->has_others) return true;
    for (int i = 0; i < ELEM_COUNT; i++)
        if (b->v[i].kind != VAL_NONE) return true;
    return false;
}

/* 追加一行说明。注意是**逐行保留**，不是拼接成一整段：
 * 数据文件里 NaN 的五行是五句独立的话，拼起来再按宽度折行会把
 * "Fire mode: …" 和 "Frost mode: …" 挤到同一行。*/
static void add_note(BossRes* b, const char* text)
{
    if (!b) return;
    if (b->n_note < RES_NOTE_LINES)
        snprintf(b->note[b->n_note++], RES_NOTE_LEN, "%s", text);
    b->is_note = true;
}

/* 去掉行内注释：'#' 在行首、或前面是空白，就把它及之后的内容丢掉。
 * 这样可以把英文原文留在行尾做参考，例如：
 *     弱点取决于它当前所处的模式。   # The weakness depends on the mode it takes.
 */
static void strip_comment(char* s)
{
    for (char* p = s; *p; p++) {
        if (*p != '#') continue;
        if (p == s || p[-1] == ' ' || p[-1] == '\t') { *p = 0; return; }
    }
}

/* 真正的解析循环：两个入口共用 */
static bool load_stream(ResTable* t, FILE* f)
{
    char line[512];
    BossRes* cur = NULL;
    bool fresh_block = true;        /* 文件开头 / 刚遇到 --- */
    int  lineno = 0;

    while (fgets(line, sizeof(line), f)) {
        lineno++;
        rtrim(line);
        strip_comment(line);
        rtrim(line);
        char* s = ltrim(line);
        if (!*s) continue;

        if (!strcmp(s, "---")) {
            cur = NULL;
            fresh_block = true;
            continue;
        }

        /* 带语言前缀的说明行：只收本语言的（没有前缀的说明行谁都收）*/
        if (cur) {
            const char* rest = NULL;
            const char* tag = note_tag(s, &rest);
            if (tag) {
                if (!strcmp(tag, TXT_LANG_TAG)) add_note(cur, rest);
                continue;
            }
        }

        char* colon = strchr(s, ':');
        if (colon && cur) {
            *colon = 0;
            char* key = rtrim(ltrim(s));
            char* val = ltrim(colon + 1);
            int e = elem_index(key);
            if (e >= 0) {
                ElemVal tmp;
                memset(&tmp, 0, sizeof(tmp));
                if (parse_value(val, &tmp)) cur->v[e] = tmp;
                else { cur->v[e].kind = VAL_NONE; t->bad_lines++; }
                continue;
            }
            if (ci_equal(key, "Others")) {
                ElemVal tmp;
                memset(&tmp, 0, sizeof(tmp));
                if (parse_value(val, &tmp) && tmp.kind == VAL_NUM) {
                    cur->has_others = true;
                    cur->others = tmp.mult;
                } else {
                    t->bad_lines++;
                }
                continue;
            }
            /* 带冒号但不是元素行 -> 当作说明（例如 "Fire mode: weakness is fire"）*/
            char joined[512];
            snprintf(joined, sizeof(joined), "%s: %s", key, val);
            add_note(cur, joined);
            continue;
        }

        /* 无冒号的行：要么是下一个 Boss 名，要么是当前 Boss 的说明。
         * 判据：文件开头 / 紧跟在 --- 之后 / 当前段已经有数值了 -> 视为新 Boss。 */
        if (fresh_block || (cur && table_started(cur)) || !cur) {
            if (t->n >= RES_MAX_BOSSES) { t->bad_lines++; continue; }
            cur = &t->b[t->n++];
            memset(cur, 0, sizeof(*cur));
            snprintf(cur->name, sizeof(cur->name), "%s", s);
            fresh_block = false;
        } else {
            add_note(cur, s);
        }
    }
    (void)lineno;
    return t->n > 0;
}

/* 窄字符路径：只有当路径是纯 ASCII、或者本来就是控制台 ANSI 编码时才可靠。
 * 从 exe 目录拼出来的绝对路径不能用它（见 res.h 的说明）。*/
bool res_load(ResTable* t, const char* path)
{
    memset(t, 0, sizeof(*t));
    FILE* f = fopen(path, "rb");
    if (!f) return false;
    bool ok = load_stream(t, f);
    fclose(f);
    return ok;
}

/* 宽字符路径：exe 同目录下的数据文件必须走这个入口 */
bool res_load_w(ResTable* t, const wchar_t* path)
{
    memset(t, 0, sizeof(*t));
    FILE* f = _wfopen(path, L"rb");
    if (!f) return false;
    bool ok = load_stream(t, f);
    fclose(f);
    return ok;
}

static const BossRes* find_exact(const ResTable* t, const char* key)
{
    for (int i = 0; i < t->n; i++)
        if (ci_equal(t->b[i].name, key)) return &t->b[i];
    return NULL;
}

const BossRes* res_find(const ResTable* t, const char* internal, int phase)
{
    if (!t || !internal || !*internal) return NULL;
    const char* disp = res_boss_display(internal);

    /* 先按形态查："Yuki" + 2 -> "Yuki(P2)" */
    if (phase < 1) phase = 1;
    char key[128];
    snprintf(key, sizeof(key), "%s(P%d)", disp, phase);
    const BossRes* r = find_exact(t, key);
    if (r) return r;

    /* 再退回不带形态的条目 */
    return find_exact(t, disp);
}
