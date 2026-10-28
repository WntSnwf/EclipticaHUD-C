/* vlog.h - VRChat 日志定位与增量读取 */
#ifndef VLOG_H
#define VLOG_H

#include <stdbool.h>
#include <wchar.h>

typedef struct VLog VLog;

/* 打开日志源。
 *   forced     : --log 指定的文件（NULL = 自动定位）。指定后只使用该文件，
 *                即使打不开也不会回退到别的日志，避免显示不相干的数据。
 *   demo       : 演示模式，不读文件，内部按真实格式生成事件行
 *   from_start : true = 从头解析（回放指定文件），false = 跳到末尾（跟随实时日志）
 */
VLog* vlog_open(const wchar_t* forced, bool demo, bool from_start);
void  vlog_close(VLog* v);

/* 返回 1 = 读出一行；0 = 暂无新行；-1 = 当前没有可用日志 */
int   vlog_poll(VLog* v, char* line, int cap);

/* 1 = 已连接日志；0 = 未找到 */
int   vlog_status(const VLog* v);

/* true = 正在跟随 --log 指定的文件（不会回退到自动定位）*/
bool  vlog_forced_only(const VLog* v);

/* 当前日志路径（未连接时为 L""）*/
const wchar_t* vlog_path(const VLog* v);

/* 上次轮询是否发生了"日志被替换/重新定位"，返回后清除标志 */
bool vlog_take_rotated(VLog* v);

#endif
