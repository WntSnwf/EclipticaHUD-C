/* parse.h - VRChat 日志行 -> Ecliptica 战斗事件
 *
 * 事件格式完全按 Ecliptica 世界 Udon 实际写入 VRChat 日志的内容解析，
 * 样例（均取自真实 output_log）：
 *
 *   2026.09.22 17:32:12 Debug      -  ECLIPTICA - now fighting boss: Amaziah(Clone) on phase: 0.4321299
 *   2026.09.22 17:36:26 Debug      -  Boss FlyLord dead, personal damage dealt:
 *   2026.09.22 17:39:32 Debug      -  damage has been taken: 4, from source: machinegunShooter2
 *   2026.09.22 17:40:53 Debug      -  Dealing 74 STRIKE damage
 *   2026.09.22 17:37:43 Debug      -  spawn token, False, 0
 *   2026.09.22 17:37:43 Debug      -  ECLIPTICA - now in stage: Stage_ProtoColony on phase: 0.1228879 as class: Nekomancer
 *   2026.09.22 17:36:37 Debug      -  ECLIPTICA saving SESSION ID 11508
 *   2026.09.22 17:07:49 Debug      -  [Behaviour] Entering Room: Ecliptica - Demo Playtest
 *   2026.09.22 17:08:33 Debug      -  [Behaviour] OnLeftRoom
 *   2026.09.22 17:08:20 Debug      -  Local controller dead, switching off.
 *   2026.09.22 17:36:26 Debug      -  STRIKE DMG: 4793
 *   2026.09.22 17:08:06 Debug      -  ownership of Amaziah transferred to SomePlayer
 */
#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>

typedef enum {
    EV_NONE = 0,
    EV_ROOM_ENTER,       /* 进入房间（text = 世界名） */
    EV_ROOM_JOIN,        /* [Behaviour] Joining wrld_... */
    EV_ROOM_LEFT,        /* [Behaviour] OnLeftRoom / 退出应用 */
    EV_RUN_START,        /* 进入 Ecliptica 世界（本局开始） */
    EV_RUN_END,          /* 离开 Ecliptica 世界（本局结束） */
    EV_STAGE,            /* ECLIPTICA - now in stage: ... */
    EV_INTERMISSION,     /* ECLIPTICA - now in intermission */
    EV_LOBBY,            /* ECLIPTICA - now in lobby */
    EV_BOSS_FIGHT,       /* ECLIPTICA - now fighting boss: X(Clone) on phase: p */
    EV_BOSS_DEAD,        /* Boss X dead, personal damage dealt: */
    EV_STRIKE_TOTAL,     /* STRIKE DMG: n */
    EV_NON_STRIKE_TOTAL, /* NON-STRIKE DMG: n */
    EV_DEALT,            /* Dealing n STRIKE/NON-STRIKE damage */
    EV_DAMAGE_TAKEN,     /* damage has been taken: n, from source: s */
    EV_OWNERSHIP,        /* ownership of <object> transferred to <player> */
    EV_PLAYER_DEAD,      /* Local controller dead, switching off. */
    EV_TOKEN_SPAWN,      /* spawn token, True/False, n */
    EV_SESSION_SAVE,     /* ECLIPTICA saving SESSION ID n */
    EV_ENEMY_SPAWN,      /* Initializing Enemy POOL IDn as ENEMY ID k */
    EV_ENEMY_RETIRE,     /* Retiring Enemy POOL IDn */
    EV_ENEMY_NAME        /* [Behaviour] No targets to encode on X(Clone) */
} EventType;

#define EV_NAME_CAP   64
#define EV_CLASS_CAP  32

typedef struct {
    EventType type;
    double    t;                    /* 日志时间戳（秒，1970 纪元；0 = 未知） */
    double    amount;               /* 伤害数值 / STRIKE 总量 / token 概率 */
    double    progress;             /* 阶段进度 0..1 */
    bool      flag;                 /* Dealing: strike？ / token: rune？ */
    int       slot;                 /* Enemy POOL ID */
    int       kind;                 /* ENEMY ID */
    char      name[EV_NAME_CAP];    /* 房间/阶段/Boss/目标玩家/伤害来源 */
    char      cls[EV_CLASS_CAP];    /* 职业 */
} Event;

/* 解析一行原始日志。识别成功返回 true 并填充 out；否则返回 false 且 out->type = EV_NONE。 */
bool parse_line(const char* raw, Event* out);

/* 解析 "YYYY.MM.DD HH:MM:SS" 时间戳（秒，1970 纪元）；失败返回 0。 */
double parse_timestamp(const char* raw);

const char* ev_type_name(EventType t);

#endif
