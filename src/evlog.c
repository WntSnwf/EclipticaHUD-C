/* evlog.c - 事件日志环形缓冲 */
#include "evlog.h"
#include "compat.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void evlog_init(EvLog* e)
{
    e->head = 0;
    e->count = 0;
}

void evlog_push(EvLog* e, double t, int kind, const char* fmt, ...)
{
    EvEntry* en = &e->buf[e->head];
    en->t = t;
    en->kind = kind;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_(en->text, sizeof(en->text), fmt, ap);
    va_end(ap);
    en->text[sizeof(en->text) - 1] = 0;
    e->head = (e->head + 1) % EVLOG_MAX;
    if (e->count < EVLOG_MAX) e->count++;
}

int evlog_count(const EvLog* e) { return e->count; }

const EvEntry* evlog_at(const EvLog* e, int idx)
{
    if (idx < 0 || idx >= e->count) return NULL;
    int i = (e->head - 1 - idx + EVLOG_MAX * 2) % EVLOG_MAX;
    return &e->buf[i];
}

static bool visible_kind(int kind, int filter)
{
    switch (filter) {
    case EVFILT_DAMAGE: return kind == EVK_DAMAGE;
    case EVFILT_TARGET: return kind == EVK_TARGET;
    case EVFILT_BOSS:   return kind == EVK_BOSS;
    default:            return true;
    }
}

int evlog_visible(const EvLog* e, int filter)
{
    int n = 0;
    for (int i = 0; i < e->count; i++) {
        const EvEntry* en = evlog_at(e, i);
        if (en && visible_kind(en->kind, filter)) n++;
    }
    return n;
}

int evlog_filter_match(int kind, int filter)
{
    return visible_kind(kind, filter) ? 1 : 0;
}
