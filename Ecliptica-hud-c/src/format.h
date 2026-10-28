/* format.h - 数值/时间格式化（不依赖 Windows，可被逻辑测试覆盖）*/
#ifndef FORMAT_H
#define FORMAT_H

/* 伤害/承伤等大数：<100000 用千分位整数，之后用 k / M */
void fmt_amount(char* buf, int cap, double v);

/* DPS：<100 保留一位小数，否则取整 */
void fmt_rate(char* buf, int cap, double v);

/* 时长 mm:ss（超过 1 小时为 h:mm:ss）*/
void fmt_duration(char* buf, int cap, double sec);

/* 墙钟 HH:MM:SS（输入为秒级时间戳）*/
void fmt_clock(char* buf, int cap, double t);

/* 整数千分位 */
void fmt_int_grouped(char* buf, int cap, long v);

#endif
