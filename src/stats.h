/* stats.h - 三级统计模型：阶段(Stage) / 本局(Run) / 本场 Boss 战(Fight)
 *
 * 语义对齐 Ecliptica 世界实际行为：
 *   - 进入 Ecliptica 系世界 -> 开新局（识别不了房间名时，靠首条
 *     "ECLIPTICA …" 日志惰性开局）
 *   - "now in stage:"        -> 切阶段（阶段内累计伤害/承伤/死亡/印记）
 *   - "now fighting boss:"   -> 开一场 Boss 战；同一 Boss 的高阶形态视为续战
 *   - "Boss X dead" + "STRIKE DMG / NON-STRIKE DMG" -> 本场击杀结算
 *   - "now in intermission"  -> 收阶段、收战斗
 *   - "OnLeftRoom" / 进入别的世界 -> 收局
 *   - "ownership of …"       -> 目标（仇恨）切换，覆盖所有敌方单位
 *   - "Local controller dead"-> 死亡（连刷按一次计）
 */
#ifndef STATS_H
#define STATS_H

#include <stdbool.h>
#include "parse.h"

#define WIN_EV          512    /* 滑动窗口事件容量 */
#define STATS_MAX_RUNS  8
#define STATS_MAX_FIGHTS 16    /* 每局 Boss 战场次 */
#define STATS_MAX_STAGES 12    /* 每局阶段数 */
#define STATS_MAX_TALLIES 16   /* 每级伤害来源条目 */
#define STATS_MAX_TARGETS 24   /* 同时记忆归属的敌方单位数 */

typedef struct { double t, v; } Sample;

/* 聚合量（无滑动窗口，可安全长期保存） */
typedef struct {
    double dmg, taken, max_hit;
    int    hits, deaths, tokens;
} Agg;

/* 某个敌方单位最近一次已知的归属（"ownership of X transferred to Y"）*/
typedef struct {
    char obj[48];
    char player[48];
} TargetSlot;

/* 伤害/来源聚合条目 */
typedef struct {
    char   who[32];
    char   attack[32];
    double total;
    int    hits;
} Tally;

/* 当前活跃统计单元（带滑动窗口，用于 DPS） */
typedef struct {
    double start_t;      /* 0 = 未开始 */
    double end_t;        /* 0 = 进行中 */
    Agg    a;
    Sample dealt[WIN_EV];
    int    dn, dh;
    Sample took[WIN_EV];
    int    tn, th;
} Unit;

typedef struct {
    char   name[48];     /* 内部名 */
    char   disp[48];     /* 显示名 */
    char   cls[32];
    double progress;
    int    stage_no;
    double start_t, end_t;
    Agg    a;
    Tally  attacks[STATS_MAX_TALLIES];
    int    n_attacks;
    bool   sealed;
} StageRec;

typedef struct {
    char   name[48];
    char   disp[48];
    int    stage_no;
    int    phase_no;
    double start_t, end_t;
    Agg    a;
    int    killed;          /* 收到 "Boss X dead" */
    int    lost;            /* 未击杀即结束 */
    double kill_strike, kill_nonstrike;
    Tally  attacks[STATS_MAX_TALLIES];
    int    n_attacks;
    bool   sealed;
} Fight;

typedef struct {
    int    number;
    char   stage[48], cls[32];
    int    last_stage_no;
    char   result[16];      /* WON / LOST / LOBBY / LEFT */
    double start_t, end_t;
    Agg    a;
    int    targets;         /* 仇恨/目标切换次数 */
    int    kills;
    Fight  fights[STATS_MAX_FIGHTS];
    int    n_fights;
    StageRec stages[STATS_MAX_STAGES];
    int    n_stages;
} Run;

typedef struct {
    bool   in_world, in_run, in_fight, in_stage, intermission;
    char   world[64];

    /* 当前阶段 */
    char   stage[48], stage_disp[48], cls[32];
    double stage_progress;
    int    stage_no;
    bool   stage_boss_seen;
    int    pending_tokens;     /* spawn token 已经出现 */
    int    level_tokens;       /* 本阶段印记总数 */

    Unit   stage_u, run_u, fight_u;
    StageRec cur_stage;
    Fight    cur_fight;
    Run      cur_run;

    Run    runs[STATS_MAX_RUNS];
    int    n_runs;

    double last_t;
    int    targets_total;
    char   target_obj[48];     /* 最近一次目标切换的对象（Boss / 杂兵 / 召唤物…） */
    char   target_player[48];  /* 该对象当前的接管玩家 */
    double target_since;

    /* 每个对象最近一次已知的归属，用于判断"目标是否真的变了"。
     * 追踪范围覆盖所有敌方单位，不只 Boss。*/
    TargetSlot targets[STATS_MAX_TARGETS];
    int    n_targets;

    /* 本局出现过的 Boss（仅用于界面上区分"这是 Boss 的目标"）*/
    char   bosses[8][48];
    int    n_bosses;

    int    view_run;           /* -1 = 跟随当前 */
    int    view_fight;         /* -1 = 最新一场 */

    char   last_text[96];      /* 最近一条事件描述（供状态栏） */
    double last_death_t;       /* 上次计入的死亡时间 */
    double alive_t;            /* 最近一次"还活着"的证据时间 */
} Stats;

void stats_init(Stats* s);
/* 处理一条事件；返回 false 表示该事件被判为噪声（未采纳），调用方无需记录 */
bool stats_on_event(Stats* s, const Event* e);

/* 视图：把当前状态整理成绘图需要的只读快照 */
typedef struct {
    bool   live;                /* true = 显示当前局，false = 显示历史局 */
    bool   in_world, in_run, in_fight, intermission;
    const char* world;
    const char* stage_name;     /* 显示名 */
    const char* cls;
    double stage_progress;
    int    stage_no;

    Agg    stage, run, fight;
    double stage_dps, run_dps, fight_dps, taken_per_sec;

    double run_elapsed, fight_elapsed, stage_elapsed;

    const char* boss;           /* 当前/查看中的 Boss 显示名，可为空串 */
    int    boss_phase;
    const char* target;         /* 目标玩家（Boss 优先，否则最近一次切换）*/
    const char* target_obj;     /* 该目标对应的对象名 */
    double target_secs;         /* 该目标已持续秒数 */
    bool   target_is_boss;      /* 该目标是否属于当前 Boss */
    const char* result;         /* 历史局结果文本，可为空串 */
    int    run_number;
    int    kills, targets, tokens, level_tokens;
    int    stage_tokens;

    const Tally* attacks;
    int    n_attacks;
    int    attacks_scope;       /* 0 = 本场, 1 = 本阶段, 2 = 本局 */

    int    view_run_index;      /* -1 = 当前 */
    int    view_fight_index;
    int    run_count, fight_count;
} StatsView;

void stats_view(const Stats* s, double now, double win, StatsView* v);

/* 历史翻页（返回是否发生变化） */
bool stats_view_run_step(Stats* s, int dir);
bool stats_view_fight_step(Stats* s, int dir);

#endif
