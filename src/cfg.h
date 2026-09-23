/* cfg.h - 配置持久化（exe 同目录 config.ini）*/
#ifndef CFG_H
#define CFG_H

#include <windows.h>
#include <stdbool.h>

#define CFG_ALPHA_MIN 40
#define CFG_ALPHA_MAX 255
#define CFG_SCALE_MIN 60
#define CFG_SCALE_MAX 200
#define CFG_SCALE_STEP 10

typedef struct {
    bool  always_on_top;
    int   alpha;          /* CFG_ALPHA_MIN..CFG_ALPHA_MAX */
    int   scale;          /* CFG_SCALE_MIN..CFG_SCALE_MAX（百分比） */
    int   stat_window;    /* DPS 统计窗口秒数 3/5/10/30/60/120 */
    bool  show_event_log;
    int   win_x, win_y;   /* 窗口位置（-1 = 自动居中偏上） */
    int   ev_filter;      /* EVFILT_* */
    /* 额外的 Ecliptica 系世界名别名（用 | 或 , 分隔）。官方名 "Ecliptica"
     * 与已知改版 "男生女生向前冲" 已内置，这里用于其它换皮世界。 */
    char  world_names[192];
} Config;

void cfg_default(Config* c);
bool cfg_load(Config* c, const wchar_t* path);
void cfg_save(const Config* c, const wchar_t* path);
void cfg_path_w(wchar_t* buf, int cap);   /* exe 同目录 config.ini */
void cfg_path_a(char* buf, int cap);

#endif
