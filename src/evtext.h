/* evtext.h - 事件 -> 事件日志文本（overlay 与 preview 共用） */
#ifndef EVTEXT_H
#define EVTEXT_H

#include "evlog.h"
#include "stats.h"
#include "parse.h"

/* 把一条已由 stats_on_event 处理过的事件写进事件日志 */
void evtext_push(EvLog* ev, const Stats* st, const Event* e);

#endif
