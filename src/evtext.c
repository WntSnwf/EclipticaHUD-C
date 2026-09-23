/* evtext.c - 事件日志文本生成 */
#include "evtext.h"
#include "zhtext.h"
#include "format.h"
#include "names.h"
#include "compat.h"

void evtext_push(EvLog* ev, const Stats* st, const Event* e)
{
    char n1[64], n2[64];
    switch (e->type) {
    case EV_ROOM_ENTER:
        evlog_push(ev, e->t, EVK_BOSS, TXT_EV_WORLD_IN, e->name);
        break;
    case EV_ROOM_LEFT:
        evlog_push(ev, e->t, EVK_BOSS, "%s", TXT_EV_WORLD_OUT);
        break;
    case EV_STAGE:
        evlog_push(ev, e->t, EVK_BOSS, TXT_EV_STAGE, st->stage_no, stage_display(e->name));
        break;
    case EV_INTERMISSION:
        evlog_push(ev, e->t, EVK_BOSS, "%s", TXT_EV_INTERM);
        break;
    case EV_LOBBY:
        evlog_push(ev, e->t, EVK_BOSS, "%s", TXT_EV_LOBBY);
        break;
    case EV_BOSS_FIGHT:
        boss_label(e->name, n1, sizeof(n1));
        evlog_push(ev, e->t, EVK_BOSS, TXT_EV_BOSS, n1);
        break;
    case EV_BOSS_DEAD:
        boss_label(e->name, n1, sizeof(n1));
        evlog_push(ev, e->t, EVK_BOSS, TXT_EV_BOSS_DOWN, n1);
        break;
    case EV_DEALT:
        fmt_amount(n1, sizeof(n1), e->amount);
        evlog_push(ev, e->t, EVK_OTHER, TXT_EV_DEALT, n1);
        break;
    case EV_DAMAGE_TAKEN: {
        char who[32], atk[32];
        source_display(e->name, who, sizeof(who), atk, sizeof(atk));
        fmt_amount(n1, sizeof(n1), e->amount);
        if (e->name[0])
            evlog_push(ev, e->t, EVK_DAMAGE, TXT_EV_TAKEN, n1, who, atk);
        else
            evlog_push(ev, e->t, EVK_DAMAGE, TXT_EV_TAKEN_1, n1, atk);
        break;
    }
    case EV_PLAYER_DEAD:
        evlog_push(ev, e->t, EVK_DEATH, "%s", TXT_EV_DEATH);
        break;
    case EV_TOKEN_SPAWN:
        fmt_amount(n2, sizeof(n2), e->amount);
        evlog_push(ev, e->t, EVK_TOKEN, TXT_EV_TOKEN, n2);
        break;
    case EV_OWNERSHIP:
        evlog_push(ev, e->t, EVK_TARGET, TXT_EV_TARGET, e->name, e->cls);
        break;
    case EV_SESSION_SAVE:
        if (st->level_tokens > 0 && st->stage_u.a.tokens <= st->level_tokens)
            evlog_push(ev, e->t, EVK_TOKEN, "%s", TXT_EV_TOKEN_GOT);
        break;
    default:
        break;
    }
}
