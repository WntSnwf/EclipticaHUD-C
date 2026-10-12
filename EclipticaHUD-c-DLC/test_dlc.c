/* test_dlc.c - DLC 逻辑测试：数据表解析 + Boss 名称映射 + 形态查询
 *
 *   test_dlc.exe                     跑全部检查（默认读 ./Weakness&Resistance.txt）
 *   test_dlc.exe <表文件>            指定数据文件
 *   test_dlc.exe --log <日志文件>    不跑测试，只打印从日志里认出的当前 Boss
 *                                    （用来在没有窗口的环境下验证 logtail 的识别）
 */
#include "res.h"
#include "logtail.h"
#include "uitext.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static int checks = 0, fails = 0;

#define CHECK(cond, msg) do {                                   \
    checks++;                                                   \
    if (cond) printf("ok  : %s\n", msg);                        \
    else { fails++; printf("FAIL: %s\n", msg); }                \
} while (0)

static ResTable T;

static void test_parse(void)
{
    printf("\n=== 解析 ===\n");
    CHECK(T.n >= 30, "至少解析出 30 个 Boss 段落");
    CHECK(T.bad_lines == 0, "没有无法识别的行");

    /* 普通数值段 */
    const BossRes* b = res_find(&T, "FlyLord", 1);
    CHECK(b != NULL, "FlyLord -> 找到 Beelzebub 段");
    if (b) {
        CHECK(!strcmp(b->name, "Beelzebub"), "段名 = Beelzebub");
        CHECK(b->v[ELEM_FIRE].kind == VAL_NUM &&
              fabs(b->v[ELEM_FIRE].mult - 1.25) < 1e-9, "Fire = 1.25x");
        CHECK(b->v[ELEM_LUMINOUS].kind == VAL_NUM &&
              fabs(b->v[ELEM_LUMINOUS].mult - 0.5) < 1e-9, "Luminous = 0.5x");
        CHECK(b->v[ELEM_SHADOW].kind == VAL_NUM &&
              fabs(b->v[ELEM_SHADOW].mult - 1.5) < 1e-9, "Shadow = 1.5x");
        CHECK(res_verdict(b->v[ELEM_FIRE].mult) == 1, "1.25x 判为「弱」");
        CHECK(res_verdict(b->v[ELEM_LUMINOUS].mult) == -1, "0.5x 判为「抗」");
        CHECK(res_verdict(b->v[ELEM_PHYSICAL].mult) == 0, "1x 判为中性");
    }

    /* Others 行 */
    const BossRes* j3 = res_find(&T, "JimBringer", 3);
    CHECK(j3 != NULL, "JimBringer 形态 3 -> 找到 Jim C. Bringer(P3)");
    if (j3) {
        CHECK(!strcmp(j3->name, "Jim C. Bringer(P3)"), "段名 = Jim C. Bringer(P3)");
        CHECK(j3->has_others && fabs(j3->others - 0.75) < 1e-9, "Others = 0.75x");
        CHECK(j3->v[ELEM_PHYSICAL].kind == VAL_NUM &&
              fabs(j3->v[ELEM_PHYSICAL].mult - 1.0) < 1e-9, "Physical = 1x");
        CHECK(j3->v[ELEM_FIRE].kind == VAL_NONE, "Fire 未单列（走 Others）");
    }

    /* 只有说明文字的段：这里只查结构（几行、有没有被拼接），
     * 具体文字属于数据文件内容，会随维护而变，放到 test_notes() 里
     * 用临时文件按已知内容验证。 */
    const BossRes* j1 = res_find(&T, "JimBringer", 1);
    CHECK(j1 != NULL && j1->is_note, "JimBringer 形态 1 -> 说明型条目");
    if (j1) CHECK(j1->n_note == 1, "Jim P1 的说明是 1 行");

    const BossRes* nan = res_find(&T, "Nan", 1);
    CHECK(nan != NULL && nan->is_note, "Nan -> NaN 说明型条目");
    if (nan) {
        /* 数据文件里 NaN 是 5 行独立的话，必须逐行保留而不是拼成一段 */
        CHECK(nan->n_note == 5, "NaN 的说明保留 5 行（不合并成一段）");
        for (int i = 0; i < nan->n_note; i++) {
            char msg[96];
            snprintf(msg, sizeof(msg), "NaN 第 %d 行非空且不含换行/注释残留", i + 1);
            CHECK(nan->note[i][0] != 0 &&
                  strchr(nan->note[i], '#') == NULL &&
                  strchr(nan->note[i], '\n') == NULL, msg);
        }
        /* 每一行各自独立：任意两行之间不互为子串 */
        bool joined = false;
        for (int i = 0; i < nan->n_note; i++)
            for (int k = 0; k < nan->n_note; k++)
                if (i != k && strstr(nan->note[i], nan->note[k])) joined = true;
        CHECK(!joined, "各行之间没有被拼接");
    }

    /* 符号写法 */
    const BossRes* y2 = res_find(&T, "Yuki", 2);
    CHECK(y2 != NULL && y2->is_note == false, "Yuki 形态 2 -> 有数值表");
    if (y2) {
        CHECK(!strcmp(y2->name, "Yuki(P2)"), "段名 = Yuki(P2)");
        CHECK(y2->v[ELEM_FIRE].kind == VAL_WEAK, "Fire = 1+x (weak)");
        CHECK(y2->v[ELEM_FROST].kind == VAL_RESIST, "Frost = 1-x (resist)");
        CHECK(y2->v[ELEM_PHYSICAL].kind == VAL_NUM &&
              fabs(y2->v[ELEM_PHYSICAL].mult - 1.0) < 1e-9, "Physical = 1x（同段混合）");
    }
}

static void test_lookup(void)
{
    printf("\n=== 查询与映射 ===\n");

    /* 本体程序里 internal -> display 的映射必须能对上数据文件里的名字 */
    CHECK(!strcmp(res_boss_display("FlyLord"), "Beelzebub"), "FlyLord -> Beelzebub");
    CHECK(!strcmp(res_boss_display("AntKing"), "Khepri"), "AntKing -> Khepri");
    CHECK(!strcmp(res_boss_display("Obisidus"), "Irides"), "Obisidus -> Irides");
    CHECK(!strcmp(res_boss_display("ManalyteAncient"), "Abaddon"), "ManalyteAncient -> Abaddon");
    CHECK(!strcmp(res_boss_display("JackedPumpkin"), "Jacked O' Lantern"), "JackedPumpkin 映射");
    CHECK(!strcmp(res_boss_display("M41D"), "M-41-D"), "M41D -> M-41-D");
    CHECK(!strcmp(res_boss_display("DarkMouth"), "Darkmouth"), "DarkMouth -> Darkmouth");
    CHECK(!strcmp(res_boss_display("Corus"), "Corus"), "表里没写的名字原样返回");

    /* 映射之后确实都能查到 */
    static const char* pairs[][2] = {
        { "FlyLord", "Beelzebub" }, { "AntKing", "Khepri" }, { "Obisidus", "Irides" },
        { "ManalyteAncient", "Abaddon" }, { "JackedPumpkin", "Jacked O' Lantern" },
        { "M41D", "M-41-D" }, { "QueenBug", "Vesra" }, { "BuffNoob", "Buff Noob" },
        { "BlackLily", "The Black Lily" }, { "Melon", "Melgor Johnson" },
        { "Gravetender", "The Gravetender" }, { "ConeHead", "Cone Head" },
        { "GoldenGrouch", "Golden Grouch" }, { "Oone", "O-One" }, { "NeoPilot", "Neo Pilot" },
        { "DarkMouth", "Darkmouth" }, { "Nan", "NaN" },
    };
    for (size_t i = 0; i < sizeof(pairs) / sizeof(pairs[0]); i++) {
        const BossRes* r = res_find(&T, pairs[i][0], 1);
        char msg[160];
        snprintf(msg, sizeof(msg), "%s 能查到段（%s）", pairs[i][0], pairs[i][1]);
        CHECK(r != NULL, msg);
    }

    /* 数据文件里直接写内部名的那些（没有映射）也要能查到 */
    static const char* plain[] = {
        "Maxipuss", "Kakarot", "Pride", "Steven", "Kodama", "NX-Obsidian",
        "Middleman", "Amaziah", "Despair", "Corus", "Yuki", "Mephiel",
        "Pandora", "Bravera"
    };
    for (size_t i = 0; i < sizeof(plain) / sizeof(plain[0]); i++) {
        char msg[128];
        snprintf(msg, sizeof(msg), "%s 能查到段", plain[i]);
        CHECK(res_find(&T, plain[i], 1) != NULL, msg);
    }
}

static void test_names(void)
{
    printf("\n=== 名称工具 ===\n");
    char b[64];

    res_boss_base("Yuki", b, sizeof(b));
    CHECK(!strcmp(b, "Yuki"), "Yuki 基础名 = Yuki");
    res_boss_base("YukiPhase2", b, sizeof(b));
    CHECK(!strcmp(b, "Yuki"), "YukiPhase2 基础名 = Yuki");
    res_boss_base("YukiPhase2(Clone)", b, sizeof(b));
    CHECK(!strcmp(b, "Yuki"), "YukiPhase2(Clone) 基础名 = Yuki");
    res_boss_base("JimBringer(Clone)", b, sizeof(b));
    CHECK(!strcmp(b, "JimBringer"), "JimBringer(Clone) 基础名 = JimBringer");
    res_boss_base("M41D", b, sizeof(b));
    CHECK(!strcmp(b, "M41D"), "M41D 不被误伤");
    res_boss_base("ManalyteAncientPhase3(Clone)", b, sizeof(b));
    CHECK(!strcmp(b, "ManalyteAncient"), "ManalyteAncientPhase3 基础名");

    CHECK(res_boss_phase("Yuki") == 1, "无后缀 -> 形态 1");
    CHECK(res_boss_phase("YukiPhase2") == 2, "YukiPhase2 -> 形态 2");
    CHECK(res_boss_phase("JimBringerPhase3(Clone)") == 3, "JimBringerPhase3 -> 形态 3");

    /* 缺数据的 Boss 不能崩，返回 NULL 即可 */
    CHECK(res_find(&T, "NoSuchBoss", 1) == NULL, "未知 Boss 返回 NULL");
    CHECK(res_find(&T, "", 1) == NULL, "空名字返回 NULL");
    CHECK(res_find(&T, NULL, 1) == NULL, "NULL 返回 NULL");

    /* JimBringer 形态 2：数据表里补的是"All damage blocked."这种说明型条目 */
    const BossRes* j2 = res_find(&T, "JimBringer", 2);
    CHECK(j2 != NULL, "JimBringer 形态 2 -> 能查到（表里已补）");
    if (j2) {
        CHECK(!strcmp(j2->name, "Jim C. Bringer(P2)"), "段名 = Jim C. Bringer(P2)");
        CHECK(j2->is_note, "形态 2 是说明型条目");
        CHECK(j2->n_note == 1, "形态 2 的说明是 1 行");
        if (j2->n_note == 1)
            CHECK(j2->note[0][0] != 0 && strchr(j2->note[0], '#') == NULL,
                  "形态 2 的说明非空且没有注释残留");
        CHECK(!j2->has_others, "形态 2 没有 Others 行");
    }
    /* 三个形态必须各自独立、不串台 */
    {
        const BossRes* p1 = res_find(&T, "JimBringer", 1);
        const BossRes* p3 = res_find(&T, "JimBringer", 3);
        CHECK(p1 && j2 && p3 && p1 != j2 && j2 != p3 && p1 != p3,
              "P1 / P2 / P3 是三个不同条目");
    }

    /* 显示名按语言来自 uitext_*.h：这里验证的是"接上了、七个、互不相同"，
     * 具体文字属于各语言的文案表，不在这里钉死。 */
    bool all_named = true, dup = false;
    for (int i = 0; i < ELEM_COUNT; i++) {
        const char* n = res_elem_name(i);
        if (!n || !n[0]) all_named = false;
        for (int k = i + 1; k < ELEM_COUNT; k++)
            if (n && res_elem_name(k) && !strcmp(n, res_elem_name(k))) dup = true;
    }
    CHECK(all_named, "七个元素都有显示名");
    CHECK(!dup, "七个显示名互不相同");
    CHECK(ELEM_COUNT == 7, "共 7 个元素");
    {
        /* TXT_ELEM_DISPLAY 是初始化列表，只能这样取出来比 */
        static const char* const disp[ELEM_COUNT] = TXT_ELEM_DISPLAY;
        bool same = true;
        for (int i = 0; i < ELEM_COUNT; i++)
            if (strcmp(res_elem_name(i), disp[i]) != 0) same = false;
        CHECK(same, "显示名逐个取自本语言的文案表");
    }

    /* 数据文件里的键与界面语言无关，三种语言版都认同一套键 */
    CHECK(!strcmp(res_elem_key(ELEM_PHYSICAL), "Physical"), "数据文件键 Physical");
    CHECK(!strcmp(res_elem_key(ELEM_FIRE), "Fire"), "数据文件键 Fire");
    CHECK(!strcmp(res_elem_key(ELEM_POISON), "Poison"), "数据文件键 Poison");
}

/* --log 模式：只验证 logtail 能不能从真实日志里认出当前 Boss */
static int probe_log(const char* path)
{
    wchar_t wpath[MAX_PATH];
    /* 控制台传进来的 argv 是 ANSI（中文 Windows 下是 GBK），不是 UTF-8 */
    MultiByteToWideChar(CP_ACP, 0, path, -1, wpath, MAX_PATH);

    LogTail lt;
    logtail_open(&lt, wpath);
    if (!logtail_ready(&lt)) {
        printf(TXT_P_OPENFAIL "\n", path);
        logtail_close(&lt);
        return 2;
    }
    logtail_poll(&lt);                       /* 再读一次新增部分 */

    char name[80];
    logtail_name(&lt, name, sizeof(name));
    printf("%s %s\n", TXT_P_LOG, name);
    printf("%s %s\n", TXT_P_FIGHTING, lt.in_fight && lt.boss[0] ? lt.boss : TXT_P_NONE);
    if (lt.in_fight && lt.boss[0]) {
        const char* disp = res_boss_display(lt.boss);
        printf("%s %s\n", TXT_P_DISPLAY, disp);
        printf("%s %d\n", TXT_P_PHASE, lt.phase);
        char key[128];
        snprintf(key, sizeof(key), "%s(P%d)", disp, lt.phase);
        printf("%s %s  /  %s\n", TXT_P_QUERY, key, disp);
    }

    /* 顺便验证查表结果 */
    static ResTable P;
    if (res_load(&P, "Weakness&Resistance.txt") && lt.in_fight && lt.boss[0]) {
        const BossRes* r = res_find(&P, lt.boss, lt.phase);
        if (r) {
            printf("%s %s\n", TXT_P_ENTRY, r->name);
            for (int i = 0; i < ELEM_COUNT; i++) {
                const ElemVal* v = &r->v[i];
                /* 显示名 + 数据文件里的键；两者相同时（英文版）只打一遍 */
                char lab[64];
                const char* dn = res_elem_name(i);
                const char* ky = res_elem_key(i);
                if (!strcmp(dn, ky)) snprintf(lab, sizeof(lab), "%s", dn);
                else                  snprintf(lab, sizeof(lab), "%s %s", dn, ky);
                const char* verdict = "-";
                char val[32];
                snprintf(val, sizeof(val), "—");

                if (v->kind == VAL_NUM) {
                    int k = res_verdict(v->mult);
                    verdict = k > 0 ? TXT_VAL_WEAK : (k < 0 ? TXT_VAL_RESIST : "-");
                    snprintf(val, sizeof(val), "%.2fx", v->mult);
                    printf("  %-18s %-7s %s\n", lab, val, verdict);
                } else if (v->kind == VAL_WEAK || v->kind == VAL_RESIST) {
                    printf("  %-18s %s%s\n", lab,
                           v->kind == VAL_WEAK ? TXT_VAL_WEAK : TXT_VAL_RESIST, TXT_P_NOMULT);
                } else if (r->has_others) {
                    int k = res_verdict(r->others);
                    verdict = k > 0 ? TXT_VAL_WEAK : (k < 0 ? TXT_VAL_RESIST : "-");
                    snprintf(val, sizeof(val), "%.2fx", r->others);
                    printf("  %-18s %-7s %s   (Others)\n", lab, val, verdict);
                } else {
                    printf("  %-18s —\n", lab);
                }
            }
            /* 说明是多行保存的，逐行打印 */
            for (int i = 0; i < r->n_note; i++)
                printf("%s %s\n", i == 0 ? TXT_P_NOTE : "            ", r->note[i]);
        } else {
            printf("%s %s\n", TXT_P_ENTRY, TXT_P_MISSING);
        }
    }
    logtail_close(&lt);
    return 0;
}

/* 数据文件里直接用中文键（物/火/冰/电/光/暗/毒）也应该能解析。
 * 显示名是中文，但解析键两种都认，维护数据表时少一层对照。 */
static void test_cn_keys(void)
{
    printf("\n=== 数据文件用中文键 ===\n");
    const char* path = "_tmp_cn_table.txt";
    FILE* f = fopen(path, "wb");
    if (!f) { CHECK(false, "无法写临时文件"); return; }
    fprintf(f,
            "TestBossCN\n"
            "物: 1x\n"
            "火: 1.25x\n"
            "冰: 0.75x\n"
            "电: 1x\n"
            "光: 0.5x\n"
            "暗: 1.5x\n"
            "毒: 1x\n"
            "---\n"
            "TestBossHoly\n"
            "圣: 0.25x\n"
            "---\n"
            /* 日文写法与中文不同的那几个必须也能当键用，
             * 否则日文用户照着面板上的字写进数据文件会解析不了 */
            "TestBossJp\n"
            "氷: 0.75x\n"
            "電気: 1.25x\n"
            "闇: 1.5x\n"
            "光: 0.5x\n"
            "---\n");
    fclose(f);

    ResTable C;
    bool ok = res_load(&C, path);
    CHECK(ok, "中文键的数据文件能加载");
    if (ok) {
        CHECK(C.bad_lines == 0, "中文键没有产生无法识别的行");
        const BossRes* b = res_find(&C, "TestBossCN", 1);
        CHECK(b != NULL, "查到 TestBossCN");
        if (b) {
            CHECK(fabs(b->v[ELEM_PHYSICAL].mult - 1.00) < 1e-9, "物 = 1x");
            CHECK(fabs(b->v[ELEM_FIRE].mult - 1.25) < 1e-9, "火 = 1.25x");
            CHECK(fabs(b->v[ELEM_FROST].mult - 0.75) < 1e-9, "冰 = 0.75x");
            CHECK(fabs(b->v[ELEM_ELECTRIC].mult - 1.00) < 1e-9, "电 = 1x");
            CHECK(fabs(b->v[ELEM_LUMINOUS].mult - 0.5) < 1e-9, "光 = 0.5x");
            CHECK(fabs(b->v[ELEM_SHADOW].mult - 1.5) < 1e-9, "暗 = 1.5x");
            CHECK(fabs(b->v[ELEM_POISON].mult - 1.00) < 1e-9, "毒 = 1x");
        }
        /* 光 / 圣 都指向 Luminous */
        const BossRes* h = res_find(&C, "TestBossHoly", 1);
        CHECK(h != NULL && fabs(h->v[ELEM_LUMINOUS].mult - 0.25) < 1e-9, "圣 = Luminous");

        /* 日文写法（与中文不同形的那些）也要能当键 */
        const BossRes* jp = res_find(&C, "TestBossJp", 1);
        CHECK(jp != NULL, "日文键的表能查到");
        if (jp) {
            CHECK(fabs(jp->v[ELEM_FROST].mult - 0.75) < 1e-9, "氷 = Frost（中文是「冰」）");
            CHECK(fabs(jp->v[ELEM_ELECTRIC].mult - 1.25) < 1e-9, "電気 = Electric（中文是「电」）");
            CHECK(fabs(jp->v[ELEM_SHADOW].mult - 1.5) < 1e-9, "闇 = Shadow（中文是「暗」）");
            CHECK(fabs(jp->v[ELEM_LUMINOUS].mult - 0.5) < 1e-9, "光 = Luminous（中日同形）");
            CHECK(C.bad_lines == 0, "日文键没有产生无法识别的行");
        }
    }
    remove(path);
}

/* 说明文字与注释：用临时文件按已知内容验证解析行为，
 * 不依赖随维护而变的那份数据文件。 */
static void test_notes(void)
{
    printf("\n=== 说明文字 / 注释 ===\n");
    const char* path = "_tmp_note_table.txt";
    FILE* f = fopen(path, "wb");
    if (!f) { CHECK(false, "无法写临时文件"); return; }
    fprintf(f,
            "EnNote\n"
            "The weakness depends on the mode it takes.\n"
            "Fire mode: weakness is fire\n"
            "---\n"
            "CnNote\n"
            "弱点取决于它当前所处的模式。          # The weakness depends on the mode it takes.\n"
            "火模式：弱点是火                      # Fire mode: weakness is fire\n"
            "---\n"
            "NoSpace\n"
            "标签#不是注释\n"                     /* # 前面没有空白 -> 不算注释 */
            "---\n"
            "OnlyComment\n"
            "# 整行都是注释\n"
            "真内容\n"
            "---\n"
            "Tagged\n"
            "zh: 中文说明\n"
            "en: English note\n"
            "ja: 日本語の説明\n"
            "无前缀说明\n"
            "---\n");
    fclose(f);

    ResTable C;
    bool ok = res_load(&C, path);
    CHECK(ok, "说明测试表能加载");
    if (ok) {
        CHECK(C.bad_lines == 0, "没有无法识别的行");

        /* 英文说明：逐行保留 */
        const BossRes* en = res_find(&C, "EnNote", 1);
        CHECK(en && en->n_note == 2, "英文说明保留 2 行");
        if (en && en->n_note == 2) {
            CHECK(!strcmp(en->note[0], "The weakness depends on the mode it takes."),
                  "英文第 1 行原样");
            CHECK(!strcmp(en->note[1], "Fire mode: weakness is fire"),
                  "英文第 2 行原样");
        }

        /* 中文说明 + 行尾英文注释 */
        const BossRes* cn = res_find(&C, "CnNote", 1);
        CHECK(cn && cn->n_note == 2, "中文说明保留 2 行");
        if (cn && cn->n_note == 2) {
            CHECK(!strcmp(cn->note[0], "弱点取决于它当前所处的模式。"),
                  "中文第 1 行，行尾 # 注释被去掉");
            CHECK(!strcmp(cn->note[1], "火模式：弱点是火"),
                  "中文第 2 行，行尾 # 注释被去掉");
            CHECK(strchr(cn->note[0], '#') == NULL, "注释没有残留");
        }

        /* # 前面没有空白 -> 是正文的一部分 */
        const BossRes* ns = res_find(&C, "NoSpace", 1);
        CHECK(ns && ns->n_note == 1 && !strcmp(ns->note[0], "标签#不是注释"),
              "紧贴文字的 # 不当注释");

        /* 整行注释被跳过，不留空行 */
        const BossRes* oc = res_find(&C, "OnlyComment", 1);
        CHECK(oc && oc->n_note == 1 && !strcmp(oc->note[0], "真内容"),
              "整行注释被跳过");

        /* 语言前缀：只收本语言的，以及没有前缀的（三种语言都收）*/
        const BossRes* tg = res_find(&C, "Tagged", 1);
        CHECK(tg && tg->n_note == 2, "语言前缀：只留本语言 + 无前缀");
        if (tg && tg->n_note == 2) {
            const char* want = !strcmp(TXT_LANG_TAG, "zh") ? "中文说明"
                             : !strcmp(TXT_LANG_TAG, "en") ? "English note"
                                                           : "日本語の説明";
            char msg[96];
            snprintf(msg, sizeof(msg), "本语言(%s)的说明被留下", TXT_LANG_TAG);
            CHECK(!strcmp(tg->note[0], want), msg);
            CHECK(!strcmp(tg->note[1], "无前缀说明"), "无前缀的说明谁都收");
            /* 别的语言的行不能漏进来 */
            CHECK(strcmp(tg->note[0], "中文说明") != 0 ||
                  !strcmp(TXT_LANG_TAG, "zh"), "没有混入别语言的说明");
        }
    }
    remove(path);
}

int main(int argc, char** argv)
{
    if (argc > 2 && !strcmp(argv[1], "--log")) return probe_log(argv[2]);

    const char* path = argc > 1 ? argv[1] : "Weakness&Resistance.txt";
    if (!res_load(&T, path)) {
        printf("无法读取数据文件: %s\n", path);
        printf("（请在 DLC 目录下运行，或把表文件路径作为参数传入）\n");
        return 2;
    }
    printf("已加载 %s：%d 个 Boss 段落\n", path, T.n);

    test_parse();
    test_lookup();
    test_names();
    test_notes();
    test_cn_keys();

    printf("\n%s：%d 项检查，%d 项失败\n", fails ? "失败" : "全部通过", checks, fails);
    return fails ? 1 : 0;
}
