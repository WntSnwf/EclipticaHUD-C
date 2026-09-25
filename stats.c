/* stats.c - 三级统计模型实现 */
#include "stats.h"
#include "names.h"
#include "compat.h"
#include <string.h>

/* ---------------- 基础 ---------------- */

static void unit_start(Unit* u, double t)
{
    memset(u, 0, sizeof(*u));
    u->start_t = t;
}

static void unit_push(Sample* buf, int* head, int* n, double t, double v)
{
    buf[*head].t = t;
    buf[*head].v = v;
    *head = (*head + 1) % WIN_EV;
    if (*n < WIN_EV) (*n)++;
}

static void unit_add_dealt(Unit* u, double t, double v)
{
    u->a.dmg += v;
    unit_push(u->dealt, &u->dh, &u->dn, t, v);
}

static void unit_add_taken(Unit* u, double t, double v)
{
    u->a.taken += v;
    u->a.hits++;
    if (v > u->a.max_hit) u->a.max_hit = v;
    unit_push(u->took, &u->th, &u->tn, t, v);
}

static double win_sum(const Sample* buf, int n, int head, double now, double win)
{
    double sum = 0;
    for (int i = 0; i < n; i++) {
        int idx = (head - 1 - i + WIN_EV * 2) % WIN_EV;
        if (buf[idx].t >= now - win) sum += buf[idx].v;
    }
    return sum;
}

static double unit_rate(const Unit* u, const Sample* buf, int n, int head,
                        double now, double win)
{
    if (n == 0) return 0;
    double sum = win_sum(buf, n, head, now, win);
    double span = now - u->start_t;
    if (span < 0) span = 0;
    double eff = win < span ? win : span;
    if (eff < 1e-6) return 0;
    return sum / eff;
}

static double unit_dps(const Unit* u, double now, double win)
{
    return unit_rate(u, u->dealt, u->dn, u->dh, now, win);
}

static double unit_tps(const Unit* u, double now, double win)
{
    return unit_rate(u, u->took, u->tn, u->th, now, win);
}

/* 累加 (who, attack) 分布；表满时淘汰总量最小的条目 */
static void tally_add(Tally* list, int* n, const char* who, const char* attack, double amount)
{
    for (int i = 0; i < *n; i++) {
        if (!strcmp(list[i].who, who) && !strcmp(list[i].attack, attack)) {
            list[i].total += amount;
            list[i].hits++;
            return;
        }
    }
    int slot = -1;
    if (*n < STATS_MAX_TALLIES) {
        slot = (*n)++;
    } else {
        int min_i = 0;
        for (int i = 1; i < *n; i++)
            if (list[i].total < list[min_i].total) min_i = i;
        if (list[min_i].total >= amount) {
            list[min_i].total += amount;
            list[min_i].hits++;
            return;
        }
        slot = min_i;
    }
    Tally* t = &list[slot];
    memset(t, 0, sizeof(*t));
    strncpy(t->who, who, sizeof(t->who) - 1);
    strncpy(t->attack, attack, sizeof(t->attack) - 1);
    t->total = amount;
    t->hits = 1;
}

static void copy_str(char* dst, int cap, const char* src)
{
    if (cap <= 0) return;
    if (!src) { dst[0] = 0; return; }
    strncpy(dst, src, (size_t)cap - 1);
    dst[cap - 1] = 0;
}

/* ---------------- 生命周期 ---------------- */

void stats_init(Stats* s)
{
    memset(s, 0, sizeof(*s));
    s->view_run = -1;
    s->view_fight = -1;
}

static void open_run(Stats* s, double t)
{
    memset(&s->cur_run, 0, sizeof(s->cur_run));
    s->cur_run.number = s->n_runs + 1;
    s->cur_run.start_t = t;
    unit_start(&s->run_u, t);
    unit_start(&s->stage_u, t);
    unit_start(&s->fight_u, t);
    memset(&s->cur_stage, 0, sizeof(s->cur_stage));
    memset(&s->cur_fight, 0, sizeof(s->cur_fight));
    s->in_run = true;
    s->in_stage = false;
    s->in_fight = false;
    s->stage_no = 0;
    s->targets_total = 0;
    s->stage_boss_seen = false;
    s->pending_tokens = 0;
    s->level_tokens = 0;
    s->stage[0] = 0;
    s->stage_disp[0] = 0;
    s->cls[0] = 0;
    s->stage_progress = 0;
    s->target_player[0] = 0;
    s->target_obj[0] = 0;
    s->target_since = 0;
    s->n_targets = 0;
    s->last_death_t = 0;
    s->alive_t = 0;
    s->n_bosses = 0;
    s->n_bosses = 0;
    s->view_run = -1;
    s->view_fight = -1;
}

static void remember_boss(Stats* s, const char* name)
{
    char base[48];
    boss_base(name, base, sizeof(base));
    if (!base[0]) return;
    for (int i = 0; i < s->n_bosses; i++)
        if (!strcmp(s->bosses[i], base)) return;
    if (s->n_bosses < 8) {
        snprintf_(s->bosses[s->n_bosses], sizeof(s->bosses[0]), "%s", base);
        s->n_bosses++;
    }
}

static bool is_known_boss(const Stats* s, const char* name)
{
    char base[48];
    boss_base(name, base, sizeof(base));
    for (int i = 0; i < s->n_bosses; i++)
        if (!strcmp(s->bosses[i], base)) return true;
    return false;
}

/* ---------------- 目标（归属）追踪 ---------------- */

/* 找出对象对应的槽位；没有则新建（表满时淘汰最久未更新的一个）*/
static int target_slot(Stats* s, const char* obj)
{
    for (int i = 0; i < s->n_targets; i++)
        if (!strcmp(s->targets[i].obj, obj)) return i;
    if (s->n_targets < STATS_MAX_TARGETS) {
        int i = s->n_targets++;
        memset(&s->targets[i], 0, sizeof(s->targets[i]));
        copy_str(s->targets[i].obj, sizeof(s->targets[i].obj), obj);
        return i;
    }
    memmove(&s->targets[0], &s->targets[1], (STATS_MAX_TARGETS - 1) * sizeof(TargetSlot));
    memset(&s->targets[STATS_MAX_TARGETS - 1], 0, sizeof(TargetSlot));
    copy_str(s->targets[STATS_MAX_TARGETS - 1].obj, sizeof(s->targets[0].obj), obj);
    return STATS_MAX_TARGETS - 1;
}

/* 常量版本：按对象名查归属。
 *
 * 必须**先精确匹配对象名**再退回基础名匹配：JimBringer 的各个形态会以
 * JimBringer / JimBringerPhase2 / JimBringerPhase3 三个不同对象名出现，
 * 基础名都是 JimBringer。若直接按基础名取第一个命中，二阶段就会一直显示
 * 一阶段遗留的目标。
 * 基础名兜底时取"最近一次变化"的那条，避免再次拿到过期数据。 */
static const TargetSlot* target_find_const(const Stats* s, const char* obj)
{
    char base[64];
    boss_base(obj, base, sizeof(base));

    for (int i = 0; i < s->n_targets; i++)
        if (!strcmp(s->targets[i].obj, obj)) return &s->targets[i];

    const TargetSlot* best = NULL;
    for (int i = 0; i < s->n_targets; i++) {
        char b2[64];
        boss_base(s->targets[i].obj, b2, sizeof(b2));
        if (strcmp(b2, base)) continue;
        if (!best || s->targets[i].t > best->t) best = &s->targets[i];
    }
    return best;
}

/* 记录一次"还活着"的证据（攻击 / 受伤 / 换阶段 / 开 Boss 战 / 出现印记）*/
static void mark_alive(Stats* s, double t)
{
    if (t > s->alive_t) s->alive_t = t;
}

static void open_stage(Stats* s, const char* name, double progress, const char* cls, double t)
{
    memset(&s->cur_stage, 0, sizeof(s->cur_stage));
    copy_str(s->cur_stage.name, sizeof(s->cur_stage.name), name);
    copy_str(s->cur_stage.disp, sizeof(s->cur_stage.disp), stage_display(name));
    if (cls && *cls) copy_str(s->cur_stage.cls, sizeof(s->cur_stage.cls), cls);
    s->cur_stage.progress = progress;
    s->cur_stage.stage_no = s->stage_no;
    s->cur_stage.start_t = t;
    s->cur_stage.sealed = false;

    unit_start(&s->stage_u, t);
    s->in_stage = true;
    s->stage_boss_seen = false;

    /* 紧邻阶段行之前的 "spawn token" 属于这个新阶段 */
    s->level_tokens = s->pending_tokens;
    s->pending_tokens = 0;

    copy_str(s->stage, sizeof(s->stage), name);
    copy_str(s->stage_disp, sizeof(s->stage_disp), stage_display(name));
    s->stage_progress = progress;
}

static void seal_stage(Stats* s, double t)
{
    if (!s->in_stage) return;
    s->cur_stage.sealed = true;
    s->cur_stage.end_t = t;
    s->cur_stage.a = s->stage_u.a;
    if (s->cur_run.n_stages < STATS_MAX_STAGES)
        s->cur_run.stages[s->cur_run.n_stages++] = s->cur_stage;
    s->in_stage = false;
}

static void fight_set_name(Fight* f, const char* name)
{
    char base[64];
    boss_base(name, base, sizeof(base));
    copy_str(f->name, sizeof(f->name), name);
    copy_str(f->disp, sizeof(f->disp), boss_display(base));
    f->phase_no = boss_phase_no(name);
}

static void open_fight(Stats* s, const char* name, double t)
{
    memset(&s->cur_fight, 0, sizeof(s->cur_fight));
    fight_set_name(&s->cur_fight, name);
    s->cur_fight.stage_no = s->stage_no;
    s->cur_fight.start_t = t;
    s->cur_fight.sealed = false;

    unit_start(&s->fight_u, t);
    s->in_fight = true;
    s->view_fight = -1;
}

static void seal_fight(Stats* s, double t, bool killed, bool lost)
{
    if (!s->in_fight) return;
    s->cur_fight.sealed = true;
    s->cur_fight.end_t = t;
    s->cur_fight.a = s->fight_u.a;
    s->cur_fight.killed = killed ? 1 : 0;
    s->cur_fight.lost = (!killed && lost) ? 1 : 0;
    if (killed) s->cur_run.kills++;
    if (s->cur_run.n_fights < STATS_MAX_FIGHTS)
        s->cur_run.fights[s->cur_run.n_fights++] = s->cur_fight;
    s->in_fight = false;
}

static void seal_run(Stats* s, double t, const char* result)
{
    if (!s->in_run) return;
    s->cur_run.end_t = t;
    s->cur_run.a = s->run_u.a;
    s->cur_run.last_stage_no = s->stage_no;
    s->cur_run.targets = s->targets_total;
    copy_str(s->cur_run.stage, sizeof(s->cur_run.stage), s->stage_disp);
    copy_str(s->cur_run.cls, sizeof(s->cur_run.cls), s->cls);
    copy_str(s->cur_run.result, sizeof(s->cur_run.result), result);

    if (s->n_runs < STATS_MAX_RUNS) {
        s->runs[s->n_runs++] = s->cur_run;
    } else {
        memmove(&s->runs[0], &s->runs[1], (STATS_MAX_RUNS - 1) * sizeof(Run));
        s->runs[STATS_MAX_RUNS - 1] = s->cur_run;
    }
    s->in_run = false;
    s->view_run = -1;
    s->view_fight = -1;
}

/* ---------------- 事件处理 ---------------- */

/* 团灭：全队阵亡后会被送回初始大厅从头再来，本局数据必须清零。
 *
 * 判据（两条都取自真实日志）：
 *   1) **Boss 还没死就进了间歇期** —— 战斗不是靠击杀结束的，那就是打输了。
 *      正常流程一定是 "Boss X dead" 先把战斗收尾，再 "now in intermission"，
 *      所以此时 in_fight 仍为真就说明这一场没打赢。
 *   2) **已经打过至少一个阶段，又冒出 Stage_Hall of Beginnings** —— 被送回初始大厅。
 *      实测 output_log_2026-09-21_15-24-01 的阶段序列是
 *      GMBigcity | Bringer | **Hall of Beginnings** | GMFuncFlat | ...，
 *      初始大厅出现在第 3 个阶段而不是开头，正是团灭重开。
 *
 * 处理：把这一局按"失败"收尾（保留在历史里，可用底部 ◀ ▶ 回看），
 * 然后立刻开一局新的，三级统计与阶段号全部归零。 */
static void wipe_run(Stats* s, double t)
{
    if (s->in_fight) seal_fight(s, t, false, true);
    if (s->in_stage) seal_stage(s, t);
    s->in_stage = false;
    s->in_fight = false;
    if (!s->in_run) return;
    seal_run(s, t, "LOST");
    open_run(s, t);
    s->in_world = true;
}

/* 是否是初始大厅那个阶段（团灭后会被送回这里）*/
static bool is_hall_of_beginnings(const char* stage_name)
{
    return stage_name && strstr(stage_name, "Hall of Beginnings") != NULL;
}

/* 惰性开局：房间名可能与官方不同，也可能压根没看到房间行（HUD 从日志尾部
 * 才开始跟随）。只要出现了 ECLIPTICA 系战斗日志，就说明确实在该世界里，
 * 此时补开一局。 */
static void ensure_run(Stats* s, double t)
{
    if (s->in_run) return;
    open_run(s, t);
    s->in_world = true;
    s->intermission = false;
    if (!s->world[0]) copy_str(s->world, sizeof(s->world), "Ecliptica");
}

/* 事件是否被采纳（false = 噪声，不必写进事件日志） */
bool stats_on_event(Stats* s, const Event* e)
{
    double t = e->t;
    if (t <= 0) t = s->last_t > 0 ? s->last_t + 0.001 : 0;
    s->last_t = t;

    switch (e->type) {
    case EV_ROOM_ENTER: {
        bool is_ecl = names_is_ecl_world(e->name);
        if (s->in_fight) seal_fight(s, t, false, true);
        if (s->in_stage) seal_stage(s, t);
        if (s->in_run) seal_run(s, t, "LEFT");
        copy_str(s->world, sizeof(s->world), e->name);
        if (is_ecl) {
            open_run(s, t);
            s->in_world = true;
        } else {
            s->in_world = false;
        }
        s->intermission = false;
        break;
    }

    case EV_ROOM_LEFT:
        if (s->in_fight) seal_fight(s, t, false, true);
        if (s->in_stage) seal_stage(s, t);
        if (s->in_run) seal_run(s, t, "LEFT");
        s->in_world = false;
        s->intermission = false;
        break;

    case EV_LOBBY:
        if (s->in_fight) seal_fight(s, t, false, true);
        if (s->in_stage) seal_stage(s, t);
        if (s->in_run) seal_run(s, t, "LOBBY");
        s->in_world = false;
        s->intermission = false;
        break;

    case EV_STAGE: {
        ensure_run(s, t);
        mark_alive(s, t);
        bool same = s->in_stage && !strcmp(s->stage, e->name);
        /* 已经打过至少一个阶段，又回到初始大厅 = 团灭重开。
         * 必须排除"同一条阶段行重复上报"（日志里很常见），否则回声也会被当成团灭。*/
        if (!same && s->stage_no >= 1 && is_hall_of_beginnings(e->name))
            wipe_run(s, t);
        if (!same) {
            if (s->in_fight) seal_fight(s, t, false, true);
            if (s->in_stage) seal_stage(s, t);
            s->stage_no++;
            open_stage(s, e->name, e->progress, e->cls, t);
        } else {
            s->stage_progress = e->progress;
            s->cur_stage.progress = e->progress;
            if (s->pending_tokens > 0) {
                s->level_tokens = s->pending_tokens;
                s->pending_tokens = 0;
            }
        }
        if (e->cls[0]) copy_str(s->cls, sizeof(s->cls), e->cls);
        s->intermission = false;
        s->in_world = true;
        break;
    }

    case EV_INTERMISSION:
        /* Boss 没死就进间歇期 = 团灭：本局要清零重来 */
        if (s->in_fight) wipe_run(s, t);
        else if (s->in_stage) seal_stage(s, t);
        s->intermission = true;
        break;

    case EV_BOSS_FIGHT: {
        ensure_run(s, t);
        mark_alive(s, t);
        if (s->in_fight) {
            char base_new[64], base_cur[64];
            boss_base(e->name, base_new, sizeof(base_new));
            boss_base(s->cur_fight.name, base_cur, sizeof(base_cur));
            int phase_new = boss_phase_no(e->name);
            if (!strcmp(base_cur, base_new) && phase_new <= s->cur_fight.phase_no)
                return false;                             /* 日志回声，忽略 */
            if (!strcmp(base_cur, base_new)) {
                /* 同一 Boss 的下一形态：续战，合并进同一场记录 */
                fight_set_name(&s->cur_fight, e->name);
                s->stage_boss_seen = true;
                return false;
            }
            seal_fight(s, t, false, false);
        }
        open_fight(s, e->name, t);
        remember_boss(s, e->name);
        s->stage_boss_seen = true;
        s->intermission = false;
        break;
    }

    case EV_BOSS_DEAD:
        if (!s->in_fight) return false;
        {
            char a[64], b[64];
            boss_base(s->cur_fight.name, a, sizeof(a));
            boss_base(e->name, b, sizeof(b));
            if (strcmp(a, b)) return false;              /* 不是当前这一只 */
            /* 基础名相同但形态不同：只可能是**上一形态的击杀行迟到**。
             * 真实日志里 JimBringerPhase3 在 19:12:21 开战，19:12:22 才吐出
             * "Boss JimBringerPhase2 dead"，若只比较基础名就会把三阶段当场结束，
             * 于是三阶段被当成"当前没有 Boss 战"。这里要求名字完全一致，
             * 或形态号一致，才认为打的是当前这一场。*/
            if (strcmp(s->cur_fight.name, e->name) != 0 &&
                boss_phase_no(e->name) != s->cur_fight.phase_no)
                return false;

            s->cur_fight.kill_strike = 0;
            s->cur_fight.kill_nonstrike = 0;
            seal_fight(s, t, true, false);
        }
        break;

    case EV_STRIKE_TOTAL:
        if (s->in_fight) s->cur_fight.kill_strike = e->amount;
        else if (s->cur_run.n_fights > 0)
            s->cur_run.fights[s->cur_run.n_fights - 1].kill_strike = e->amount;
        break;

    case EV_NON_STRIKE_TOTAL:
        if (s->in_fight) s->cur_fight.kill_nonstrike = e->amount;
        else if (s->cur_run.n_fights > 0)
            s->cur_run.fights[s->cur_run.n_fights - 1].kill_nonstrike = e->amount;
        break;

    case EV_DEALT:
        ensure_run(s, t);
        mark_alive(s, t);
        /* 间歇期里唯一能打的是练习木桩（实测固定每次 30 点，刷屏式输出 20 多次）。
         * 那不是战斗伤害，三级统计都不该收 —— 否则本局伤害会凭空多出几百点。*/
        if (s->intermission) return false;
        unit_add_dealt(&s->run_u, t, e->amount);
        if (s->in_fight) unit_add_dealt(&s->fight_u, t, e->amount);
        else if (s->in_stage) unit_add_dealt(&s->stage_u, t, e->amount);
        break;

    case EV_DAMAGE_TAKEN: {
        ensure_run(s, t);
        mark_alive(s, t);
        unit_add_taken(&s->run_u, t, e->amount);
        if (s->in_fight) unit_add_taken(&s->fight_u, t, e->amount);
        else if (s->in_stage) unit_add_taken(&s->stage_u, t, e->amount);

        char who[32], atk[32];
        source_display(e->name, who, sizeof(who), atk, sizeof(atk));
        if (s->in_fight) tally_add(s->cur_fight.attacks, &s->cur_fight.n_attacks, who, atk, e->amount);
        else if (s->in_stage) tally_add(s->cur_stage.attacks, &s->cur_stage.n_attacks, who, atk, e->amount);
        break;
    }

    case EV_PLAYER_DEAD: {
        /* 一次死亡常常连刷几十行 "Local controller dead"（实测 8 秒内 34 行），
         * 而且中间还会混入 ECLIPTICA saving SESSION ID 之类的无关行。
         * 判据：必须"上次死亡之后又出现了活着的证据"才允许再计一次，
         * 再加一个静默期兜底，避免把同一次死亡的连刷算成多次。*/
        if (!s->in_run) return false;
        const double DEATH_HOLD = 3.0;
        bool prev = s->last_death_t > 0;
        bool alive_again = !prev || (s->alive_t > s->last_death_t);
        if (!alive_again) return false;
        if (prev && t - s->last_death_t < DEATH_HOLD) return false;

        s->last_death_t = t;
        s->alive_t = 0;                       /* 需要新的存活证据才能再计一次 */
        s->run_u.a.deaths++;
        if (s->in_fight) s->fight_u.a.deaths++;
        if (s->in_stage) s->stage_u.a.deaths++;
        break;
    }

    case EV_TOKEN_SPAWN:
        ensure_run(s, t);
        mark_alive(s, t);
        s->pending_tokens++;
        break;

    case EV_SESSION_SAVE:
        if (!s->in_run || !s->in_stage) return false;
        if (s->stage_boss_seen) return false;                /* Boss 已出现，存档不算印记 */
        if (s->level_tokens == 0 && s->pending_tokens > 0) {  /* token 行排在 stage 行之后的情况 */
            s->level_tokens = s->pending_tokens;
            s->pending_tokens = 0;
        }
        if (s->stage_u.a.tokens >= s->level_tokens) return false;   /* 没有待拾取印记 */
        s->stage_u.a.tokens++;
        s->run_u.a.tokens++;
        break;

    case EV_OWNERSHIP: {
        /* 追踪所有敌方单位（Boss、杂兵、召唤物、道具）的目标变化：
         * 每个对象各自记住上次的归属，只有玩家真的换了才计一次，
         * 这样同一条 ownership 反复上报不会重复计数。*/
        if (!s->in_run) return false;
        const char* obj = e->name;
        if (!obj[0] || !e->cls[0]) return false;
        int idx = target_slot(s, obj);
        if (!strcmp(s->targets[idx].player, e->cls)) return false;   /* 目标没变 */
        copy_str(s->targets[idx].player, sizeof(s->targets[idx].player), e->cls);
        s->targets[idx].t = t;

        s->targets_total++;
        copy_str(s->target_obj, sizeof(s->target_obj), obj);
        copy_str(s->target_player, sizeof(s->target_player), e->cls);
        s->target_since = t;
        break;
    }

    default:
        break;
    }
    return true;
}

/* ---------------- 视图 ---------------- */

/* 把一局里所有阶段 + 所有 Boss 战的伤害来源合并 */
static void merge_run_attacks(const Run* r, Tally* out, int* n)
{
    for (int i = 0; i < r->n_stages; i++)
        for (int j = 0; j < r->stages[i].n_attacks; j++)
            tally_add(out, n, r->stages[i].attacks[j].who,
                      r->stages[i].attacks[j].attack, r->stages[i].attacks[j].total);
    for (int i = 0; i < r->n_fights; i++)
        for (int j = 0; j < r->fights[i].n_attacks; j++)
            tally_add(out, n, r->fights[i].attacks[j].who,
                      r->fights[i].attacks[j].attack, r->fights[i].attacks[j].total);
}

void stats_view(const Stats* s, double now, double win, StatsView* v)
{
    static Tally merged[STATS_MAX_TALLIES];

    memset(v, 0, sizeof(*v));
    v->view_run_index = s->view_run;
    v->view_fight_index = s->view_fight;
    v->run_count = s->n_runs;
    v->fight_count = s->cur_run.n_fights;
    v->world = s->world;
    v->live = true;
    v->in_world = s->in_world;
    v->in_run = s->in_run;
    v->in_fight = s->in_fight;
    v->intermission = s->intermission;
    v->stage_name = s->stage_disp;
    v->cls = s->cls;
    v->stage_progress = s->stage_progress;
    v->stage_no = s->stage_no;
    v->boss = "";
    v->result = "";
    v->target = "";
    v->target_obj = "";
    v->target_secs = 0;
    v->target_is_boss = false;
    v->run_number = s->cur_run.number;
    v->attacks_scope = 2;                 /* 默认按本局聚合 */

    v->stage = s->stage_u.a;
    v->run = s->run_u.a;
    v->fight = s->fight_u.a;
    v->stage_dps = unit_dps(&s->stage_u, now, win);
    v->run_dps = unit_dps(&s->run_u, now, win);
    v->fight_dps = unit_dps(&s->fight_u, now, win);
    v->taken_per_sec = unit_tps(&s->run_u, now, win);
    v->run_elapsed = now - s->run_u.start_t;
    v->stage_elapsed = now - s->stage_u.start_t;
    v->fight_elapsed = now - s->fight_u.start_t;
    v->kills = s->cur_run.kills;
    v->targets = s->targets_total;
    v->tokens = s->run_u.a.tokens;
    v->level_tokens = s->level_tokens;
    v->stage_tokens = s->stage_u.a.tokens;
    /* 目标显示：
     *   战斗中 -> 只认这只 Boss 自己的归属；
     *   非战斗 -> 汇报最近一次目标切换（覆盖杂兵/召唤物/道具）。
     * 战斗中**不再**回落到"任意对象的最近一次切换"：日志里有些 Boss
     * （实测 FlyLord）开战后要 57 秒才吐出第一条 ownership，旧的写法会拿
     * 上一阶段的敌人冒充本场目标，看上去就是"最初仇恨目标识别不出来"。
     * 查不到就老老实实显示 — 。 */
    if (s->in_fight) {
        const TargetSlot* ts = target_find_const(s, s->cur_fight.name);
        if (ts && ts->player[0]) {
            v->target = ts->player;
            v->target_obj = ts->obj;
            v->target_is_boss = true;
            v->target_secs = ts->t > 0 ? now - ts->t : 0;   /* 该目标已锁定多久 */
            if (v->target_secs < 0) v->target_secs = 0;
        }
    } else if (s->target_player[0]) {
        v->target = s->target_player;
        v->target_obj = s->target_obj;
        v->target_secs = now - s->target_since;
        v->target_is_boss = is_known_boss(s, s->target_obj);
    }

    if (s->in_fight && s->cur_fight.n_attacks > 0) {
        v->boss = s->cur_fight.disp;
        v->boss_phase = s->cur_fight.phase_no;
        v->attacks = s->cur_fight.attacks;
        v->n_attacks = s->cur_fight.n_attacks;
        v->attacks_scope = 0;
    } else if (s->in_stage) {
        v->boss = s->in_fight ? s->cur_fight.disp : "";
        v->boss_phase = s->in_fight ? s->cur_fight.phase_no : 0;
        v->attacks = s->cur_stage.attacks;
        v->n_attacks = s->cur_stage.n_attacks;
        v->attacks_scope = 1;
    } else if (s->in_fight) {
        v->boss = s->cur_fight.disp;
        v->boss_phase = s->cur_fight.phase_no;
        v->attacks_scope = 0;
    }

    /* 不在战斗/阶段中时，按本局（或最近一局）汇总伤害来源 */
    if (!s->in_fight && !s->in_stage) {
        int mn = 0;
        memset(merged, 0, sizeof(merged));
        if (s->in_run) merge_run_attacks(&s->cur_run, merged, &mn);
        else if (s->n_runs > 0) merge_run_attacks(&s->runs[s->n_runs - 1], merged, &mn);
        v->attacks = merged;
        v->n_attacks = mn;
        v->attacks_scope = 2;
    }

    /* 说明：离开本局后刻意保留最后一段阶段/最后一场战斗的数据，
     * 让面板在"等待进入 Ecliptica"时仍能回看刚刚这一局。 */

    /* 历史局视图：用聚合量覆盖 */
    /* 历史局视图：用聚合量覆盖 */
    if (s->view_run >= 0 && s->view_run < s->n_runs) {
        const Run* r = &s->runs[s->view_run];
        v->live = false;
        v->run_number = r->number;
        v->run = r->a;
        v->run_elapsed = r->end_t - r->start_t;
        v->stage = r->a;
        v->fight = r->a;
        v->stage_dps = r->end_t > r->start_t ? r->a.dmg / (r->end_t - r->start_t) : 0;
        v->run_dps = v->stage_dps;
        v->fight_dps = 0;
        v->taken_per_sec = r->end_t > r->start_t ? r->a.taken / (r->end_t - r->start_t) : 0;
        v->result = r->result;
        v->kills = r->kills;
        v->targets = r->targets;
        v->tokens = r->a.tokens;
        v->level_tokens = 0;
        v->stage_tokens = 0;
        v->stage_no = r->last_stage_no;
        v->stage_name = r->stage;
        v->cls = r->cls;
        v->stage_progress = 0;
        v->boss = "";
        v->in_fight = false;
        v->in_run = false;
        v->fight_count = r->n_fights;

        int mn = 0;
        memset(merged, 0, sizeof(merged));
        merge_run_attacks(r, merged, &mn);
        v->attacks = merged;
        v->n_attacks = mn;
        v->attacks_scope = 2;

        if (s->view_fight >= 0 && s->view_fight < r->n_fights) {
            const Fight* f = &r->fights[s->view_fight];
            v->boss = f->disp;
            v->boss_phase = f->phase_no;
            v->fight = f->a;
            v->fight_elapsed = f->end_t - f->start_t;
            v->fight_dps = v->fight_elapsed > 0 ? f->a.dmg / v->fight_elapsed : 0;
            v->attacks = f->attacks;
            v->n_attacks = f->n_attacks;
            v->attacks_scope = 0;
            v->in_fight = true;
            v->result = f->killed ? "WON" : (f->lost ? "LOST" : "OPEN");
        }
    } else if (s->view_fight >= 0 && s->view_fight < s->cur_run.n_fights) {
        const Fight* f = &s->cur_run.fights[s->view_fight];
        v->boss = f->disp;
        v->boss_phase = f->phase_no;
        v->fight = f->a;
        v->fight_elapsed = f->end_t - f->start_t;
        v->fight_dps = v->fight_elapsed > 0 ? f->a.dmg / v->fight_elapsed : 0;
        v->attacks = f->attacks;
        v->n_attacks = f->n_attacks;
        v->attacks_scope = 0;
        v->result = f->killed ? "WON" : (f->lost ? "LOST" : "OPEN");
    }
}

bool stats_view_run_step(Stats* s, int dir)
{
    if (s->n_runs <= 0) return false;
    int next = s->view_run + dir;
    if (next < -1) next = s->n_runs - 1;
    if (next >= s->n_runs) next = -1;
    if (next < -1) next = -1;
    bool changed = next != s->view_run;
    s->view_run = next;
    s->view_fight = -1;
    return changed;
}

bool stats_view_fight_step(Stats* s, int dir)
{
    int total;
    if (s->view_run >= 0 && s->view_run < s->n_runs) total = s->runs[s->view_run].n_fights;
    else total = s->cur_run.n_fights;
    if (total <= 0) return false;
    int next = s->view_fight + dir;
    if (next < -1) next = total - 1;
    if (next >= total) next = -1;
    if (next < -1) next = -1;
    bool changed = next != s->view_fight;
    s->view_fight = next;
    return changed;
}
