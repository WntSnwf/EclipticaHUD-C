/* overlay.h - 覆盖层窗口 */
#ifndef OVERLAY_H
#define OVERLAY_H

#include "cfg.h"

/* 创建窗口并进入消息循环（窗口关闭后才返回） */
void overlay_run(Config* cfg, bool demo, bool from_start);

/* 指定日志文件路径（在 overlay_run 前调用；NULL = 自动定位） */
void overlay_use_log(const wchar_t* path);

#endif
