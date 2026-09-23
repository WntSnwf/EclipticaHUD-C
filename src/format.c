/* format.c - 数值/时间格式化 */
#include "format.h"
#include "compat.h"
#include <math.h>
#include <string.h>

void fmt_int_grouped(char* buf, int cap, long v)
{
    char tmp[32];
    int neg = v < 0;
    unsigned long u = neg ? (unsigned long)(-(v + 1)) + 1UL : (unsigned long)v;
    snprintf_(tmp, sizeof(tmp), "%lu", u);
    size_t n = strlen(tmp);
    int oi = 0;
    if (neg && oi < cap - 1) buf[oi++] = '-';
    for (size_t i = 0; i < n && oi < cap - 1; i++) {
        if (i > 0 && ((n - i) % 3) == 0 && oi < cap - 1) buf[oi++] = ',';
        if (oi < cap - 1) buf[oi++] = tmp[i];
    }
    if (cap > 0) buf[oi < cap ? oi : cap - 1] = 0;
}

void fmt_amount(char* buf, int cap, double v)
{
    if (v < 0) v = 0;
    if (v < 100000.0) {
        fmt_int_grouped(buf, cap, (long)(v + 0.5));
    } else if (v < 1000000.0) {
        snprintf_(buf, (size_t)cap, "%.1fk", v / 1000.0);
    } else if (v < 1000000000.0) {
        snprintf_(buf, (size_t)cap, "%.2fM", v / 1000000.0);
    } else {
        snprintf_(buf, (size_t)cap, "%.2fB", v / 1000000000.0);
    }
}

void fmt_rate(char* buf, int cap, double v)
{
    if (v < 0) v = 0;
    if (v < 100.0) snprintf_(buf, (size_t)cap, "%.1f", v);
    else if (v < 100000.0) fmt_int_grouped(buf, cap, (long)(v + 0.5));
    else snprintf_(buf, (size_t)cap, "%.1fk", v / 1000.0);
}

void fmt_duration(char* buf, int cap, double sec)
{
    if (sec < 0) sec = 0;
    long s = (long)(sec + 0.5);
    long h = s / 3600, m = (s % 3600) / 60, ss = s % 60;
    if (h > 0) snprintf_(buf, (size_t)cap, "%ld:%02ld:%02ld", h, m, ss);
    else snprintf_(buf, (size_t)cap, "%02ld:%02ld", m, ss);
}

void fmt_clock(char* buf, int cap, double t)
{
    if (t <= 0) { snprintf_(buf, (size_t)cap, "--:--:--"); return; }
    long s = (long)t;
    snprintf_(buf, (size_t)cap, "%02ld:%02ld:%02ld", (s / 3600) % 24, (s / 60) % 60, s % 60);
}
