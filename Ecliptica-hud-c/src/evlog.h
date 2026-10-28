/* evlog.h - 事件日志环形缓冲 */
#ifndef EVLOG_H
#define EVLOG_H

#include <stdbool.h>

#define EVLOG_MAX 512
#define EVLOG_TEXT 112

/* 日志过滤器 */
enum {
    EVFILT_ALL = 0,
    EVFILT_DAMAGE,     /* 仅承伤 */
    EVFILT_TARGET,     /* 仅目标/仇恨 */
    EVFILT_BOSS,       /* 仅阶段 / Boss / 局 */
    EVFILT_COUNT
};

/* 颜色分类 */
enum {
    EVK_OTHER = 0,
    EVK_DAMAGE,        /* 承伤 */
    EVK_TARGET,        /* 目标切换 */
    EVK_BOSS,          /* Boss / 阶段 / 局 */
    EVK_DEATH,
    EVK_TOKEN
};

typedef struct {
    double t;                    /* 日志时间戳（秒） */
    char   text[EVLOG_TEXT];     /* UTF-8 显示文本 */
    int    kind;
} EvEntry;

typedef struct {
    EvEntry buf[EVLOG_MAX];
    int     head;                /* 下一个写入位置 */
    int     count;
} EvLog;

void evlog_init(EvLog* e);
void evlog_push(EvLog* e, double t, int kind, const char* fmt, ...);
int  evlog_count(const EvLog* e);
/* idx = 0 表示最新一条；越界返回 NULL */
const EvEntry* evlog_at(const EvLog* e, int idx);
/* 按过滤器统计可见条数 */
int  evlog_visible(const EvLog* e, int filter);
/* 该分类是否通过过滤器：1 = 显示 */
int  evlog_filter_match(int kind, int filter);

#endif
