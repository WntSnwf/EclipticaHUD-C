/* test_core.c - 逻辑测试：解析器 + 统计模型 + 世界识别 + 格式化
 *
 * 构建运行：  mingw32-make test
 * 回放实测：  test_core.exe <日志文件>     打印事件/目标切换的统计摘要
 *
 * 测试用的日志行取自真实 VRChat output_log。
 *
 * 注意：Stats 结构体较大（几百 KB），实例一律放在静态存储区，不要放栈上。
 */
#include "src/parse.h"
#include "src/stats.h"
#include "src/evlog.h"
#include "src/evtext.h"
#include "src/format.h"
#include "src/names.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

static int fails = 0;
static int checks = 0;

#define CHECK(cond, msg) do {                           \
    checks++;                                           \
    if (!(cond)) { printf("FAIL: %s\n", msg); fails++; } \
    else printf("ok  : %s\n", msg);                     \
} while (0)

static Stats g_st;

static void feed_all(const char** lines, int n)
{
    for (int i = 0; i < n; i++) {
        Event e;
        if (!parse_line(lines[i], &e)) continue;
        stats_on_event(&g_st, &e);
    }
}

/* ---------------- 解析器 ---------------- */

static void test_parser(void)
{
    Event e;

    CHECK(parse_line("2026.09.22 17:40:53 Debug      -  Dealing 74 STRIKE damage", &e)
          && e.type == EV_DEALT && e.amount == 74 && e.flag,
          "Dealing 74 STRIKE damage");
    CHECK(parse_line("2026.09.22 17:41:40 Debug      -  Dealing 38 NON-STRIKE damage", &e)
          && e.type == EV_DEALT && e.amount == 38 && !e.flag,
          "Dealing 38 NON-STRIKE damage");
    CHECK(!parse_line("2026.09.22 17:00:00 Debug      -  Dealing 5 MAGIC damage", &e),
          "Dealing 5 MAGIC damage 应被忽略");

    CHECK(parse_line("2026.09.22 17:39:32 Debug      -  damage has been taken: 4, from source: machinegunShooter2", &e)
          && e.type == EV_DAMAGE_TAKEN && e.amount == 4 && !strcmp(e.name, "machinegunShooter2"),
          "damage has been taken (无括号来源)");
    CHECK(parse_line("2026.09.22 17:43:13 Debug      -  damage has been taken: 43, from source: (Peltapod) attack_Slam", &e)
          && e.type == EV_DAMAGE_TAKEN && e.amount == 43 && !strcmp(e.name, "(Peltapod) attack_Slam"),
          "damage has been taken (带括号来源)");
    CHECK(parse_line("2026.09.22 17:00:00 Debug      -  damage has been taken: 2, from source: ", &e)
          && e.type == EV_DAMAGE_TAKEN && e.amount == 2 && e.name[0] == 0,
          "damage has been taken (来源为空)");

    CHECK(parse_line("2026.09.22 17:32:12 Debug      -  ECLIPTICA - now fighting boss: Amaziah(Clone) on phase: 0.4321299", &e)
          && e.type == EV_BOSS_FIGHT && !strcmp(e.name, "Amaziah") && fabs(e.progress - 0.4321299) < 1e-6,
          "now fighting boss");
    CHECK(parse_line("2026.09.22 17:37:43 Debug      -  ECLIPTICA - now in stage: Stage_ProtoColony on phase: 0.1228879 as class: Nekomancer", &e)
          && e.type == EV_STAGE && !strcmp(e.name, "ProtoColony") && !strcmp(e.cls, "Nekomancer"),
          "now in stage");
    CHECK(parse_line("2026.09.22 17:36:37 Debug      -  ECLIPTICA - now in intermission", &e)
          && e.type == EV_INTERMISSION, "now in intermission");
    CHECK(parse_line("2026.09.22 17:00:00 Debug      -  ECLIPTICA - now in lobby", &e)
          && e.type == EV_LOBBY, "now in lobby");
    CHECK(parse_line("2026.09.22 17:33:05 Debug      -  ECLIPTICA saving SESSION ID 11508", &e)
          && e.type == EV_SESSION_SAVE, "saving SESSION ID");
    CHECK(!parse_line("2026.09.22 17:08:06 Debug      -  ECLIPTICA loaded SESSION ID 22442", &e),
          "loaded SESSION ID 不是事件");
    CHECK(!parse_line("2026.09.22 17:08:06 Debug      -  ECLIPTICA Loading Settings...", &e),
          "Loading Settings 不是事件");

    CHECK(parse_line("2026.09.22 17:36:26 Debug      -  Boss FlyLord dead, personal damage dealt: ", &e)
          && e.type == EV_BOSS_DEAD && !strcmp(e.name, "FlyLord"), "Boss X dead");
    CHECK(parse_line("2026.09.22 17:36:26 Debug      -  STRIKE DMG: 4793", &e)
          && e.type == EV_STRIKE_TOTAL && e.amount == 4793, "STRIKE DMG");
    CHECK(parse_line("2026.09.22 17:36:26 Debug      -  NON-STRIKE DMG: 615", &e)
          && e.type == EV_NON_STRIKE_TOTAL && e.amount == 615, "NON-STRIKE DMG");

    CHECK(parse_line("2026.09.23 13:43:17 Debug      -  [Behaviour] Entering Room: Ecliptica - Demo Playtest", &e)
          && e.type == EV_ROOM_ENTER && !strcmp(e.name, "Ecliptica - Demo Playtest"),
          "Entering Room");
    CHECK(parse_line("2026.09.23 13:28:10 Debug      -  [Behaviour] Entering Room: 测试房间", &e)
          && e.type == EV_ROOM_ENTER && !strcmp(e.name, "测试房间"),
          "Entering Room（中文世界名）");
    CHECK(parse_line("2026.09.22 17:08:33 Debug      -  [Behaviour] OnLeftRoom", &e)
          && e.type == EV_ROOM_LEFT, "OnLeftRoom");
    CHECK(parse_line("2026.09.22 17:08:20 Debug      -  Local controller dead, switching off.", &e)
          && e.type == EV_PLAYER_DEAD, "Local controller dead");
    CHECK(parse_line("2026.09.22 17:37:43 Debug      -  spawn token, True, 55", &e)
          && e.type == EV_TOKEN_SPAWN && e.flag && e.amount == 55, "spawn token True");
    CHECK(parse_line("2026.09.23 13:49:18 Debug      -  ownership of Amaziah transferred to かえで", &e)
          && e.type == EV_OWNERSHIP && !strcmp(e.name, "Amaziah") && !strcmp(e.cls, "かえで"),
          "ownership transferred（UTF-8 玩家名）");
    CHECK(parse_line("2026.09.23 13:49:18 Debug      -  ownership of Amaziah(Clone) transferred to Keiros", &e)
          && e.type == EV_OWNERSHIP && !strcmp(e.name, "Amaziah"),
          "ownership 对象名去掉 (Clone)");
    CHECK(!parse_line("  at UnityEngine.EventSystems.ExecuteEvents.Execute () [0x00000] in <0>:0 ", &e),
          "堆栈行不是事件");
    CHECK(!parse_line("2026.09.22 17:00:00 Debug      -  Tracking boss as defeated in-run.", &e),
          "Tracking boss as defeated 不是事件");
    CHECK(!parse_line("", &e), "空行不是事件");

    double t1 = parse_timestamp("2026.09.22 17:40:53 Debug      -  x");
    double t2 = parse_timestamp("2026.09.22 17:40:54 Debug      -  x");
    CHECK(fabs((t2 - t1) - 1.0) < 1e-6, "相邻秒时间戳差 = 1");
    CHECK(t1 > 1700000000.0 && t1 < 1900000000.0, "时间戳量级合理（1970 纪元秒）");
    CHECK(parse_timestamp("2026.09.06 21:44:44 Debug      -  [Behaviour] OnLeftRoom") > 0,
          "第二种分隔符也能取到时间戳");
}

/* ---------------- 名称/来源 ---------------- */

static void test_names(void)
{
    CHECK(!strcmp(boss_display("FlyLord"), "Beelzebub"), "Boss 名称映射 FlyLord");
    CHECK(!strcmp(boss_display("Kodama"), "Kodama"), "Boss 未收录名称原样返回");
    CHECK(!strcmp(stage_display("ProtoColony"), "Proto Colony"), "阶段名称映射");
    CHECK(!strcmp(stage_display("VRCHub"), "VRChat Hub"), "阶段名称映射 VRCHub");
    CHECK(!strcmp(phase_display(0.0), "Primal"), "阶段进度 0 -> Primal");
    CHECK(!strcmp(phase_display(1.0), "Eye of the Eclipse"), "阶段进度 1 -> Eye of the Eclipse");

    char lbl[64];
    boss_label("ObisidusPhase2", lbl, sizeof(lbl));
    CHECK(!strcmp(lbl, "Irides (P2)"), "boss_label 映射基础名并保留形态后缀");
    boss_label("FlyLord", lbl, sizeof(lbl));
    CHECK(!strcmp(lbl, "Beelzebub"), "boss_label 无后缀");
    boss_label("KodamaPhase3", lbl, sizeof(lbl));
    CHECK(!strcmp(lbl, "Kodama (P3)"), "boss_label 未收录名称原样保留");

    char base[64];
    boss_base("ManalyteAncientPhase2", base, sizeof(base));
    CHECK(!strcmp(base, "ManalyteAncient"), "boss_base 去除 Phase 后缀");
    boss_base("M41D", base, sizeof(base));
    CHECK(!strcmp(base, "M41D"), "boss_base 不误伤含数字名称");
    CHECK(boss_phase_no("YukiPhase3") == 3, "boss_phase_no");
    CHECK(boss_phase_no("Yuki") == 1, "boss_phase_no 无后缀 = 1");
    CHECK(is_player_summon("Neko12") && !is_player_summon("Neko"), "玩家召唤物判定");

    char who[32], atk[32];
    source_display("(Khepri) attack_Claws2", who, sizeof(who), atk, sizeof(atk));
    CHECK(!strcmp(who, "Khepri") && !strcmp(atk, "Claws 2"), "来源拆分 + 美化");
    source_display("machinegunShooter2", who, sizeof(who), atk, sizeof(atk));
    CHECK(!strcmp(who, "enemy") && !strcmp(atk, "Machinegun Shooter 2"), "无括号来源 -> enemy");
    source_display("attack_Spit (2)", who, sizeof(who), atk, sizeof(atk));
    CHECK(!strcmp(atk, "Spit"), "纯数字括号后缀被丢弃");
    source_display("NukeHitbox (BIG)", who, sizeof(who), atk, sizeof(atk));
    CHECK(!strcmp(atk, "Nuke (big)"), "非数字括号后缀保留为小写");
    source_display("([Missing Key \"e_VirtueBeam\"]) damageTick", who, sizeof(who), atk, sizeof(atk));
    CHECK(!strcmp(who, "Black Virtue") && !strcmp(atk, "Damage Tick"), "Missing Key 映射");
}

/* ---------------- 世界识别 ---------------- */

static void test_world_aliases(void)
{
    names_set_world_aliases(NULL);
    CHECK(names_is_ecl_world("Ecliptica - Demo Playtest"), "官方世界名被识别");
    CHECK(names_is_ecl_world("ecliptica"), "大小写不敏感");
    CHECK(!names_is_ecl_world("Sample Combat World"), "未登记的房间名不误判");
    CHECK(!names_is_ecl_world("Yuki Room"), "无关世界不被误判");
    CHECK(!names_is_ecl_world(""), "空世界名不被误判");

    names_set_world_aliases("Sample Combat World|另一个测试世界");
    CHECK(names_is_ecl_world("Sample Combat World"), "配置登记的世界名生效");
    CHECK(names_is_ecl_world("Sample Combat World (v2)"), "子串匹配生效");
    CHECK(names_is_ecl_world("另一个测试世界"), "配置登记的中文世界名生效");
    CHECK(!names_is_ecl_world("Cookie Clicker VR"), "未登记的其它世界仍不误判");
    names_set_world_aliases(NULL);
}

/* ---------------- 格式化 ---------------- */

static void test_format(void)
{
    char b[64];
    fmt_amount(b, sizeof(b), 7);        CHECK(!strcmp(b, "7"), "fmt_amount 小数");
    fmt_amount(b, sizeof(b), 12345);    CHECK(!strcmp(b, "12,345"), "fmt_amount 千分位");
    fmt_amount(b, sizeof(b), 250000);   CHECK(!strcmp(b, "250.0k"), "fmt_amount k");
    fmt_amount(b, sizeof(b), 7340000);  CHECK(!strcmp(b, "7.34M"), "fmt_amount M");
    fmt_rate(b, sizeof(b), 12.34);      CHECK(!strcmp(b, "12.3"), "fmt_rate 一位小数");
    fmt_rate(b, sizeof(b), 1234.0);     CHECK(!strcmp(b, "1,234"), "fmt_rate 整数千分位");
    fmt_duration(b, sizeof(b), 75);     CHECK(!strcmp(b, "01:15"), "fmt_duration 分秒");
    fmt_duration(b, sizeof(b), 3725);   CHECK(!strcmp(b, "1:02:05"), "fmt_duration 时分秒");
    fmt_amount(b, sizeof(b), 100000);   CHECK(!strcmp(b, "100.0k"), "fmt_amount 边界 100000");
}

/* ---------------- 统计：完整一局 ---------------- */

static void test_stats_run(void)
{
    static const char* script[] = {
        "2026.09.22 20:00:00 Debug      -  [Behaviour] Entering Room: Ecliptica - Demo Playtest",
        "2026.09.22 20:00:01 Debug      -  ECLIPTICA - now in stage: Stage_ProtoColony on phase: 0.1 as class: Nekomancer",
        "2026.09.22 20:00:02 Debug      -  spawn token, False, 0",
        "2026.09.22 20:00:02 Debug      -  spawn token, True, 55",
        "2026.09.22 20:00:03 Debug      -  ECLIPTICA saving SESSION ID 11508",
        "2026.09.22 20:00:04 Debug      -  Dealing 100 STRIKE damage",
        "2026.09.22 20:00:05 Debug      -  Dealing 50 NON-STRIKE damage",
        "2026.09.22 20:00:06 Debug      -  damage has been taken: 40, from source: (Khepri) attack_Claws2",
        "2026.09.22 20:00:07 Debug      -  damage has been taken: 10, from source: (Khepri) attack_Claws2",
        "2026.09.22 20:00:08 Debug      -  Local controller dead, switching off.",
        "2026.09.22 20:00:20 Debug      -  ECLIPTICA - now fighting boss: FlyLord(Clone) on phase: 0.06",
        "2026.09.22 20:00:21 Debug      -  Dealing 200 STRIKE damage",
        "2026.09.22 20:00:22 Debug      -  damage has been taken: 120, from source: (FlyLord) attack_Bite",
        "2026.09.22 20:00:23 Debug      -  ownership of FlyLord transferred to OtherPlayer",
        "2026.09.22 20:00:24 Debug      -  Boss FlyLord dead, personal damage dealt: ",
        "2026.09.22 20:00:24 Debug      -  STRIKE DMG: 4793",
        "2026.09.22 20:00:24 Debug      -  NON-STRIKE DMG: 615",
        "2026.09.22 20:00:30 Debug      -  ECLIPTICA - now in intermission",
        "2026.09.22 20:00:40 Debug      -  [Behaviour] OnLeftRoom",
    };
    const int N = (int)(sizeof(script) / sizeof(script[0]));

    stats_init(&g_st);
    feed_all(script, N);

    CHECK(!g_st.in_world && !g_st.in_run, "离开世界后 in_world / in_run 均为 false");
    CHECK(g_st.n_runs == 1, "记录到 1 局");
    CHECK(g_st.stage_no == 1, "阶段数 = 1");
    CHECK(fabs(g_st.cur_run.a.dmg - 350) < 0.01, "本局伤害 = 100+50+200 = 350");
    CHECK(fabs(g_st.cur_run.a.taken - 170) < 0.01, "本局承伤 = 40+10+120 = 170");
    CHECK(g_st.cur_run.a.hits == 3, "本局受击 = 3");
    CHECK(g_st.cur_run.a.deaths == 1, "本局死亡 = 1（连发去重）");
    CHECK(g_st.cur_run.a.tokens == 1, "本局印记 = 1");
    CHECK(g_st.cur_run.kills == 1, "本局击倒 Boss = 1");
    CHECK(g_st.cur_run.targets == 1, "Boss 目标切换 = 1");
    CHECK(g_st.cur_run.n_fights == 1, "Boss 战历史 = 1 场");
    CHECK(g_st.cur_run.n_stages == 1, "阶段历史 = 1 段");

    const Fight* f = &g_st.cur_run.fights[0];
    CHECK(!strcmp(f->disp, "Beelzebub"), "Boss 显示名 = Beelzebub");
    CHECK(f->killed == 1 && f->lost == 0, "本场已击杀");
    CHECK(fabs(f->a.dmg - 200) < 0.01, "本场伤害 = 200（阶段伤害不计入本场）");
    CHECK(fabs(f->a.taken - 120) < 0.01, "本场承伤 = 120");
    CHECK(f->kill_strike == 4793 && f->kill_nonstrike == 615, "击杀结算 STRIKE/NON-STRIKE");
    CHECK(strcmp(g_st.cur_run.result, "LEFT") == 0, "本局结果 = LEFT");

    CHECK(fabs(g_st.cur_run.stages[0].a.dmg - 150) < 0.01, "阶段伤害 = 150");
    CHECK(fabs(g_st.cur_run.stages[0].a.taken - 50) < 0.01, "阶段承伤 = 50");
    CHECK(g_st.cur_run.stages[0].a.tokens == 1, "阶段印记 = 1");

    CHECK(g_st.cur_run.stages[0].n_attacks == 1, "阶段来源条目 = 1");
    CHECK(!strcmp(g_st.cur_run.stages[0].attacks[0].who, "Khepri"), "阶段来源 who");
    CHECK(!strcmp(g_st.cur_run.stages[0].attacks[0].attack, "Claws 2"), "阶段来源 attack");
    CHECK(fabs(g_st.cur_run.stages[0].attacks[0].total - 50) < 0.01, "阶段来源总量 = 50");
    CHECK(g_st.cur_run.stages[0].attacks[0].hits == 2, "阶段来源次数 = 2");
}

/* ---------------- 统计：房间名与官方不同的世界 ---------------- */

static void test_alt_world(void)
{
    static const char* script[] = {
        "2026.09.23 13:28:10 Debug      -  [Behaviour] Entering Room: Sample Combat World",
        "2026.09.23 13:44:53 Debug      -  Dealing 59 STRIKE damage",
        "2026.09.23 13:45:43 Debug      -  ECLIPTICA - now in stage: Stage_VRCHub on phase: 0.4367217 as class: Thaumaturge",
        "2026.09.23 13:49:09 Debug      -  ECLIPTICA - now fighting boss: Amaziah(Clone) on phase: 0.4367217",
        "2026.09.23 13:49:18 Debug      -  ownership of Amaziah transferred to かえで",
        "2026.09.23 13:49:21 Debug      -  Dealing 35 STRIKE damage",
        "2026.09.23 13:50:00 Debug      -  damage has been taken: 29, from source: kickProject",
    };
    const int N = (int)(sizeof(script) / sizeof(script[0]));

    /* 未登记房间名时：进房不开局，靠 ECLIPTICA 日志惰性开局 */
    names_set_world_aliases(NULL);
    stats_init(&g_st);
    feed_all(script, N);
    CHECK(g_st.in_run && g_st.in_world, "未登记的房间名靠 ECLIPTICA 日志开局");
    CHECK(g_st.stage_no == 1, "识别到阶段");
    CHECK(!strcmp(g_st.stage_disp, "VRChat Hub"), "阶段名映射正确");
    CHECK(fabs(g_st.run_u.a.dmg - 94) < 0.01, "伤害累计 = 59+35");
    CHECK(g_st.in_fight, "识别到 Boss 战");
    CHECK(!strcmp(g_st.cur_fight.disp, "Amaziah"), "Boss 名称正确");
    CHECK(g_st.targets_total == 1, "识别到 Boss 目标切换");

    /* 用 world_names 登记后：进房即开局 */
    names_set_world_aliases("Sample Combat World");
    stats_init(&g_st);
    feed_all(script, N);
    CHECK(g_st.in_run, "登记过房间名后进房即开局");
    names_set_world_aliases(NULL);

    /* 没有房间行（HUD 从日志尾部开始跟随）时也必须能惰性开局 */
    stats_init(&g_st);
    feed_all(script + 1, N - 1);            /* 跳过 Entering Room 那一行 */
    CHECK(g_st.in_run, "缺少房间行时靠 ECLIPTICA 日志惰性开局");
    CHECK(fabs(g_st.run_u.a.dmg - 94) < 0.01, "惰性开局后伤害仍然统计");
}

/* ---------------- 统计：目标追踪（逐对象去重） ---------------- */

static void test_target_tracking(void)
{
    static const char* junk[] = {
        "EnemyController", "EnemyController (2)", "Ice Squid", "FrostSac",
        "Robowhel", "Lizord", "SpiritDeer", "LavaSac", "Manalyte",
        "Peltapod", "Furry", "Carnie", "Token4", "ConeEnforcer",
        "Big Robot", "TooTired"
    };
    Event e;

    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica"); e.t = 1;
    stats_on_event(&g_st, &e);

    /* 杂兵 / 召唤物 / 道具的归属变化同样追踪（不只 Boss）*/
    for (int i = 0; i < (int)(sizeof(junk) / sizeof(junk[0])); i++) {
        e.type = EV_OWNERSHIP;
        strcpy(e.name, junk[i]);
        strcpy(e.cls, "SomeoneElse");
        e.t = 3 + i * 0.1;
        CHECK(stats_on_event(&g_st, &e), "非 Boss 的 ownership 也被采纳");
    }
    CHECK(g_st.targets_total == 16, "16 个不同对象各计一次目标变化");

    /* 同一对象、同一目标重复上报：判为无变化，不重复计数 */
    e.type = EV_OWNERSHIP; strcpy(e.name, "Ice Squid"); strcpy(e.cls, "SomeoneElse"); e.t = 20;
    CHECK(!stats_on_event(&g_st, &e), "同一对象同一目标不重复计数");
    CHECK(g_st.targets_total == 16, "计数不变");

    /* 同一对象换人：计一次 */
    strcpy(e.cls, "PlayerB"); e.t = 21;
    CHECK(stats_on_event(&g_st, &e), "同一对象换目标被采纳");
    CHECK(g_st.targets_total == 17, "计数 +1");
    CHECK(!strcmp(g_st.target_player, "PlayerB"), "当前目标 = PlayerB");

    /* Boss 也同样追踪，并且带 (Clone) 后缀时归并到同一个对象 */
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "Amaziah"); e.t = 30;
    stats_on_event(&g_st, &e);
    e.type = EV_OWNERSHIP; strcpy(e.name, "Amaziah(Clone)"); strcpy(e.cls, "PlayerC"); e.t = 31;
    CHECK(stats_on_event(&g_st, &e), "Boss 目标切换被采纳");
    CHECK(g_st.targets_total == 18, "计数 +1");

    StatsView v;
    stats_view(&g_st, 31, 10, &v);
    CHECK(v.target && !strcmp(v.target, "PlayerC"), "视图优先给出当前 Boss 的目标");
    CHECK(v.target_is_boss, "识别出该目标是 Boss");
    CHECK(fabs(v.target_secs) < 1e-6, "目标持续时间从切换时刻起算");

    /* 没有 ownership 的世界：目标为空，界面显示占位符 */
    stats_init(&g_st);
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Sample Combat World"); e.t = 1;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "DarkMouth"); e.t = 2;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 40; e.t = 3;
    stats_on_event(&g_st, &e);
    stats_view(&g_st, 3, 10, &v);
    CHECK(v.target && v.target[0] == 0, "无 ownership 时目标为空（界面显示 —）");
    CHECK(g_st.targets_total == 0, "无 ownership 时切换次数为 0");
}

/* ---------------- 统计：死亡连刷只算一次 ---------------- */

static void test_death_burst(void)
{
    Event e;
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica"); e.t = 100;
    stats_on_event(&g_st, &e);
    e.type = EV_STAGE; strcpy(e.name, "Stage_VRCHub"); e.t = 101;
    stats_on_event(&g_st, &e);
    e.type = EV_DAMAGE_TAKEN; e.amount = 4; e.name[0] = 0; e.t = 102;
    stats_on_event(&g_st, &e);

    /* 真实日志 2026-09-23 14:33:23 起的连刷：8 秒 34 行，中间还夹了一条无关行 */
    e.type = EV_PLAYER_DEAD;
    for (int i = 0; i < 10; i++) { e.t = 103 + i * 0.5; stats_on_event(&g_st, &e); }
    /* 中间混入一条 ECLIPTICA saving SESSION ID，不应把玩家判为复活 */
    e.type = EV_SESSION_SAVE; strcpy(e.name, ""); e.t = 108; stats_on_event(&g_st, &e);
    e.type = EV_PLAYER_DEAD;
    for (int i = 0; i < 10; i++) { e.t = 108.5 + i * 0.5; stats_on_event(&g_st, &e); }
    CHECK(g_st.run_u.a.deaths == 1, "8 秒内 20 行死亡只算 1 次死亡");

    /* 复活后重新活动（打下伤害）再死：必须计第二次 */
    e.type = EV_DEALT; e.amount = 35; e.t = 130; stats_on_event(&g_st, &e);
    e.type = EV_PLAYER_DEAD; e.t = 200; stats_on_event(&g_st, &e);
    CHECK(g_st.run_u.a.deaths == 2, "复活后再次死亡计为第 2 次");

    /* 第三次：静默期内即使混进"受伤"这类存活证据，也不能立刻再计一次 */
    e.type = EV_PLAYER_DEAD; e.t = 201; stats_on_event(&g_st, &e);
    e.type = EV_PLAYER_DEAD; e.t = 202; stats_on_event(&g_st, &e);
    CHECK(g_st.run_u.a.deaths == 2, "静默期内的连刷不重复计数");
    e.type = EV_DAMAGE_TAKEN; e.amount = 5; e.name[0] = 0; e.t = 202.5;
    stats_on_event(&g_st, &e);
    e.type = EV_PLAYER_DEAD; e.t = 202.8; stats_on_event(&g_st, &e);
    CHECK(g_st.run_u.a.deaths == 2, "刚有存活证据但静默期未过，仍不计新死亡");
    e.type = EV_PLAYER_DEAD; e.t = 204; stats_on_event(&g_st, &e);
    CHECK(g_st.run_u.a.deaths == 3, "静默期过后再死计为第 3 次");
}

/* ---------------- 统计：JimBringer 多阶段（真实日志回归） ----------------
 *
 * 取自 output_log_2026-09-24_18-20-39.txt：
 *   19:01:44  ownership of JimBringer       transferred to iccti
 *   19:04:35  Boss JimBringer dead
 *   19:04:35  ECLIPTICA - now fighting boss: JimBringerPhase2(Clone)   (回声：JimBringer)
 *   19:07:19  ownership of JimBringerPhase2 transferred to てぃな xplaTina
 *   19:12:21  ECLIPTICA - now fighting boss: JimBringerPhase3(Clone)
 *   19:12:22  Boss JimBringerPhase2 dead     <- 上一形态的击杀行迟到
 *   19:24:31  Boss JimBringerPhase3 dead
 */
static void test_jim_phases(void)
{
    static const char* script[] = {
        "2026.09.24 18:57:37 Debug      -  ECLIPTICA - now in stage: Stage_Bringer on phase: 1 as class: Spellhammer",
        "2026.09.24 18:58:10 Debug      -  ECLIPTICA - now fighting boss: JimBringer(Clone) on phase: 1",
        "2026.09.24 19:01:44 Debug      -  ownership of JimBringer transferred to iccti",
        "2026.09.24 19:04:35 Debug      -  Boss JimBringer dead, personal damage dealt: ",
        "2026.09.24 19:04:35 Debug      -  ECLIPTICA - now fighting boss: JimBringerPhase2(Clone) on phase: 1",
        "2026.09.24 19:04:35 Debug      -  ECLIPTICA - now fighting boss: JimBringer(Clone) on phase: 1",
        "2026.09.24 19:04:36 Debug      -  ECLIPTICA - now fighting boss: JimBringerPhase2(Clone) on phase: 1",
        "2026.09.24 19:07:19 Debug      -  ownership of JimBringerPhase2 transferred to てぃな xplaTina",
    };
    const int N = (int)(sizeof(script) / sizeof(script[0]));
    Event e;
    StatsView v;

    stats_init(&g_st);
    feed_all(script, N);

    /* 二阶段：目标必须是二阶段自己的，而不是一阶段遗留的 iccti */
    CHECK(g_st.in_fight, "二阶段处于 Boss 战中");
    CHECK(!strcmp(g_st.cur_fight.name, "JimBringerPhase2"), "二阶段场次名 = JimBringerPhase2");
    CHECK(g_st.cur_fight.phase_no == 2, "二阶段形态号 = 2");
    stats_view(&g_st, g_st.last_t, 10, &v);
    CHECK(v.target && !strcmp(v.target, "てぃな xplaTina"),
          "二阶段显示二阶段的目标（不是一阶段遗留的 iccti）");
    CHECK(v.target_is_boss, "该目标被识别为 Boss 目标");
    CHECK(fabs(v.target_secs) < 1e-6, "目标持续时间自二阶段切换时刻起算");

    /* 三阶段开战：应当是同一只 Boss 的续战 */
    memset(&e, 0, sizeof(e));
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "JimBringerPhase3"); e.t = g_st.last_t + 1;
    stats_on_event(&g_st, &e);
    CHECK(g_st.in_fight && g_st.cur_fight.phase_no == 3, "三阶段被识别为续战");

    /* 上一形态的击杀行迟到：不能把三阶段结束掉 */
    memset(&e, 0, sizeof(e));
    e.type = EV_BOSS_DEAD; strcpy(e.name, "JimBringerPhase2"); e.t = g_st.last_t + 2;
    CHECK(!stats_on_event(&g_st, &e), "上一形态的迟到击杀行被忽略");
    CHECK(g_st.in_fight, "三阶段仍在进行中（未被误判为结束）");
    CHECK(!strcmp(g_st.cur_fight.name, "JimBringerPhase3"), "当前场次仍是 JimBringerPhase3");
    stats_view(&g_st, g_st.last_t, 10, &v);
    CHECK(v.boss && v.boss[0], "三阶段仍显示为 Boss 战");

    /* 三阶段自己的击杀行：正常结算 */
    memset(&e, 0, sizeof(e));
    e.type = EV_BOSS_DEAD; strcpy(e.name, "JimBringerPhase3"); e.t = g_st.last_t + 3;
    CHECK(stats_on_event(&g_st, &e), "三阶段击杀行被采纳");
    CHECK(!g_st.in_fight, "三阶段正常结束");
    CHECK(g_st.cur_run.n_fights == 2, "一阶段与三阶段各留一条场次记录");
    CHECK(g_st.cur_run.fights[1].killed == 1, "三阶段记为击杀");
    CHECK(g_st.cur_run.fights[1].phase_no == 3, "三阶段形态号 = 3");

    /* 续战后优先显示新形态自己的目标，而不是旧形态的残留 */
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica"); e.t = 1;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "JimBringer"); e.t = 2;
    stats_on_event(&g_st, &e);
    e.type = EV_OWNERSHIP; strcpy(e.name, "JimBringer"); strcpy(e.cls, "OldTarget"); e.t = 3;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "JimBringerPhase3"); e.t = 4;
    stats_on_event(&g_st, &e);
    e.type = EV_OWNERSHIP; strcpy(e.name, "JimBringerPhase3"); strcpy(e.cls, "NewTarget"); e.t = 5;
    stats_on_event(&g_st, &e);
    stats_view(&g_st, 5, 10, &v);
    CHECK(v.target && !strcmp(v.target, "NewTarget"), "续战后显示新形态自己的目标");
}

/* ---------------- 统计：DPS 窗口 ---------------- */

static void test_dps_window(void)
{
    Event e;
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER;
    strcpy(e.name, "Ecliptica - Demo Playtest");
    e.t = 1000;
    stats_on_event(&g_st, &e);
    e.type = EV_STAGE;
    strcpy(e.name, "ProtoColony");
    e.t = 1001;
    stats_on_event(&g_st, &e);

    for (int i = 0; i < 10; i++) {
        e.type = EV_DEALT;
        e.amount = 100;
        e.t = 1002 + i;                 /* 1002..1011 */
        stats_on_event(&g_st, &e);
    }
    StatsView v;
    stats_view(&g_st, 1012, 10, &v);
    double dps10 = v.stage_dps;
    stats_view(&g_st, 1012, 3, &v);
    double dps3 = v.stage_dps;

    CHECK(fabs(dps10 - 100.0) < 0.5, "10 秒窗口 DPS = 1000/10 = 100");
    CHECK(fabs(dps3 - 100.0) < 0.5, "3 秒窗口 DPS = 300/3 = 100");
}

/* ---------------- 统计：阶段切换 ---------------- */

static void test_stage_switch(void)
{
    Event e;
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica"); e.t = 10;
    stats_on_event(&g_st, &e);
    e.type = EV_STAGE; strcpy(e.name, "ProtoColony"); e.t = 11;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 100; e.t = 12;
    stats_on_event(&g_st, &e);
    e.type = EV_STAGE; strcpy(e.name, "LostElysia"); e.t = 20;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 300; e.t = 21;
    stats_on_event(&g_st, &e);

    CHECK(g_st.stage_no == 2, "阶段切换后 stage_no = 2");
    CHECK(!strcmp(g_st.stage_disp, "Lost Elysia"), "阶段显示名映射");
    CHECK(fabs(g_st.stage_u.a.dmg - 300) < 0.01, "新阶段只统计本阶段伤害");
    CHECK(fabs(g_st.run_u.a.dmg - 400) < 0.01, "本局累计伤害 = 400");
    CHECK(g_st.cur_run.n_stages == 1, "旧阶段已归档");
    CHECK(fabs(g_st.cur_run.stages[0].a.dmg - 100) < 0.01, "归档阶段伤害 = 100");
}

/* ---------------- 统计：Boss 续战 ---------------- */

static void test_boss_phase_continuation(void)
{
    Event e;
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica"); e.t = 1;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "Yuki"); e.t = 2;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 100; e.t = 3;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_FIGHT; strcpy(e.name, "YukiPhase2"); e.t = 4;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 500; e.t = 5;
    stats_on_event(&g_st, &e);
    e.type = EV_BOSS_DEAD; strcpy(e.name, "YukiPhase2"); e.t = 6;
    stats_on_event(&g_st, &e);

    CHECK(g_st.cur_run.n_fights == 1, "同一 Boss 的下一形态合并为一场");
    CHECK(fabs(g_st.cur_run.fights[0].a.dmg - 600) < 0.01, "续战伤害累计 = 600");
    CHECK(g_st.cur_run.fights[0].phase_no == 2, "续战阶段号更新为 2");
    CHECK(!strcmp(g_st.cur_run.fights[0].disp, "Yuki"), "续战显示名不含形态后缀");
    CHECK(g_st.cur_run.kills == 1, "续战击杀计数 = 1");

    e.type = EV_BOSS_FIGHT; strcpy(e.name, "YukiPhase2"); e.t = 7;
    stats_on_event(&g_st, &e);
    CHECK(g_st.cur_run.n_fights == 1, "重复 Boss 行不新增场次");
}

/* ---------------- 统计：跨世界 ---------------- */

static void test_other_world_leaves(void)
{
    Event e;
    stats_init(&g_st);
    memset(&e, 0, sizeof(e));
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica - Demo Playtest"); e.t = 1;
    stats_on_event(&g_st, &e);
    e.type = EV_DEALT; e.amount = 50; e.t = 2;
    stats_on_event(&g_st, &e);
    e.type = EV_ROOM_ENTER; strcpy(e.name, "Yuki Room"); e.t = 3;
    stats_on_event(&g_st, &e);

    CHECK(!g_st.in_run && !g_st.in_world, "进入别的世界会结束本局");
    CHECK(g_st.n_runs == 1 && fabs(g_st.runs[0].a.dmg - 50) < 0.01, "本局已归档且伤害正确");
    CHECK(!strcmp(g_st.world, "Yuki Room"), "世界名已更新");
}

/* ---------------- 事件日志 ---------------- */

static void test_evlog(void)
{
    EvLog ev;
    evlog_init(&ev);
    for (int i = 0; i < 5; i++) evlog_push(&ev, i, i == 2 ? EVK_DAMAGE : EVK_OTHER, "line%d", i);
    CHECK(evlog_count(&ev) == 5, "事件日志计数");
    CHECK(!strcmp(evlog_at(&ev, 0)->text, "line4"), "evlog_at(0) 为最新");
    CHECK(!strcmp(evlog_at(&ev, 4)->text, "line0"), "evlog_at(4) 为最旧");
    CHECK(evlog_at(&ev, 5) == NULL, "越界返回 NULL");
    CHECK(evlog_visible(&ev, EVFILT_ALL) == 5, "过滤器 全部 = 5");
    CHECK(evlog_visible(&ev, EVFILT_DAMAGE) == 1, "过滤器 承伤 = 1");
    CHECK(evlog_visible(&ev, EVFILT_TARGET) == 0, "过滤器 目标 = 0");

    for (int i = 0; i < EVLOG_MAX + 3; i++) evlog_push(&ev, i, EVK_OTHER, "x%d", i);
    CHECK(evlog_count(&ev) == EVLOG_MAX, "环形缓冲封顶");
    CHECK(!strcmp(evlog_at(&ev, 0)->text, "x514"), "环形覆盖后最新条目正确");
    CHECK(!strcmp(evlog_at(&ev, EVLOG_MAX - 1)->text, "x3"), "环形覆盖后最旧条目正确");
}

/* ---------------- 命令行回放摘要（实测调参用） ---------------- */

static Stats g_rp;
static EvLog g_rpev;

static void replay_summary(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (!f) { printf("cannot open %s\n", path); return; }
    stats_init(&g_rp);
    evlog_init(&g_rpev);
    char line[2048];
    long n = 0, evs = 0, kept = 0, own_all = 0, own_kept = 0;
    while (fgets(line, sizeof(line), f)) {
        size_t l = strlen(line);
        while (l > 0 && (line[l - 1] == '\n' || line[l - 1] == '\r')) line[--l] = 0;
        n++;
        Event e;
        if (!parse_line(line, &e)) continue;
        evs++;
        if (e.type == EV_OWNERSHIP) own_all++;
        if (stats_on_event(&g_rp, &e)) {
            kept++;
            if (e.type == EV_OWNERSHIP) {
                own_kept++;
                evtext_push(&g_rpev, &g_rp, &e);
            }
        }
    }
    fclose(f);
    printf("lines=%ld  events=%ld  accepted=%ld\n", n, evs, kept);
    printf("ownership: parse %ld -> keep %ld (per-object, target really changed)\n",
           own_all, own_kept);
    int tot_deaths = 0, tot_kills = 0, tot_targets = 0;
    for (int i = 0; i < g_rp.n_runs; i++) {
        tot_deaths += g_rp.runs[i].a.deaths;
        tot_kills += g_rp.runs[i].kills;
        tot_targets += g_rp.runs[i].targets;
    }
    printf("runs=%d  in_run=%d  stage_no=%d  targets_total=%d\n",
           g_rp.n_runs, g_rp.in_run, g_rp.stage_no, g_rp.targets_total);
    printf("all runs: deaths=%d  kills=%d  targets=%d\n", tot_deaths, tot_kills, tot_targets);
    printf("run: dmg=%.0f taken=%.0f hits=%d deaths=%d tokens=%d fights=%d stages=%d\n",
           g_rp.run_u.a.dmg, g_rp.run_u.a.taken, g_rp.run_u.a.hits,
           g_rp.run_u.a.deaths, g_rp.run_u.a.tokens,
           g_rp.cur_run.n_fights, g_rp.cur_run.n_stages);
}

int main(int argc, char** argv)
{
    if (argc > 1) { replay_summary(argv[1]); return 0; }

    printf("=== 解析器 ===\n");              test_parser();
    printf("\n=== 名称/来源 ===\n");         test_names();
    printf("\n=== 世界识别 ===\n");          test_world_aliases();
    printf("\n=== 格式化 ===\n");            test_format();
    printf("\n=== 统计：完整一局 ===\n");     test_stats_run();
    printf("\n=== 统计：异名世界 ===\n");     test_alt_world();
    printf("\n=== 统计：目标追踪 ===\n");     test_target_tracking();
    printf("\n=== 统计：死亡连刷 ===\n");     test_death_burst();
    printf("\n=== 统计：Jim 多阶段 ===\n");   test_jim_phases();
    printf("\n=== 统计：DPS 窗口 ===\n");     test_dps_window();
    printf("\n=== 统计：阶段切换 ===\n");     test_stage_switch();
    printf("\n=== 统计：Boss 续战 ===\n");    test_boss_phase_continuation();
    printf("\n=== 统计：跨世界 ===\n");       test_other_world_leaves();
    printf("\n=== 事件日志 ===\n");           test_evlog();

    printf("\n%s：%d 项检查，%d 项失败\n", fails ? "失败" : "全部通过", checks, fails);
    return fails ? 1 : 0;
}
