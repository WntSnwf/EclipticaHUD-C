/* logtail.h - 跟随 VRChat 日志，判断"当前正在打哪个 Boss"
 *
 * 只关心一件事：从日志里认出当前 Boss（内部名 + 形态号）。
 * 本体程序 ecliptica-hud-c 做全量解析，这里刻意保持极简，两边互不影响。
 */
#ifndef LOGTAIL_H
#define LOGTAIL_H

/* 需要 Win7 以上的 API（GetTickCount64 等）*/
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    FILE*   f;
    wchar_t path[MAX_PATH];
    bool    forced;                    /* 由 --log 指定：绝不回退到自动定位 */
    bool    ready;                     /* 文件已打开 */
    double  rescan_t;                  /* 上次重新找日志的时间（GetTickCount64 秒）*/

    /* 当前 Boss */
    char    boss[64];                  /* 内部名（已去掉 (Clone)/Phase 后缀）*/
    int     phase;                     /* 形态号，无后缀 = 1 */
    bool    in_fight;
} LogTail;

/* 打开并**从头**扫一遍当前日志，以便立刻知道正打到哪。
 * forced 非空时只用这一个文件；打不开则 ready=false 且不再自动找别的。 */
void logtail_open(LogTail* lt, const wchar_t* forced);

/* 读取新增内容。返回 true 表示"当前 Boss"发生了变化。 */
bool logtail_poll(LogTail* lt);

void logtail_close(LogTail* lt);

/* 当前日志文件名（不含目录），UTF-8，便于显示；无日志时返回空串 */
void logtail_name(const LogTail* lt, char* out, int cap);

bool logtail_ready(const LogTail* lt);

#endif
