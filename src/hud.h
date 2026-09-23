/* hud.h - HUD 布局与 GDI 绘制
 *
 * 布局由 hud_layout() 统一计算，绘制与命中测试共用同一份矩形，
 * 因此界面各区块不会互相压盖。
 */
#ifndef HUD_H
#define HUD_H

#include <windows.h>
#include <stdbool.h>
#include "cfg.h"
#include "stats.h"
#include "evlog.h"

/* 逻辑基准尺寸（100% 缩放）*/
#define HUD_BASE_W 460
#define HUD_BASE_H 620

enum HudBtn {
    HUD_BTN_NONE = 0,
    HUD_BTN_TOPMOST,
    HUD_BTN_BIGGER,
    HUD_BTN_SMALLER,
    HUD_BTN_OPAQUE,
    HUD_BTN_TRANSPARENT,
    HUD_BTN_WIN_LONGER,
    HUD_BTN_WIN_SHORTER,
    HUD_BTN_LOG,
    HUD_BTN_CLOSE,
    HUD_BTN_PREV_RUN,
    HUD_BTN_NEXT_RUN,
    HUD_BTN_PREV_FIGHT,
    HUD_BTN_NEXT_FIGHT,
    HUD_BTN_LOG_UP,
    HUD_BTN_LOG_DOWN,
    /* 事件日志过滤器：顺序必须与 EVFILT_* 一致，便于 HUD_BTN_FILT_ALL + i */
    HUD_BTN_FILT_ALL,
    HUD_BTN_FILT_DAMAGE,
    HUD_BTN_FILT_TARGET,
    HUD_BTN_FILT_BOSS,
    HUD_BTN_DRAG
};

#define HUD_BAR_BTN_N 8

typedef struct {
    bool log_on;
    RECT title;          /* 标题行（含关闭按钮）*/
    RECT bar;            /* 按钮行 */
    RECT close_btn;
    RECT bar_btn[HUD_BAR_BTN_N];
    RECT info;           /* 阶段/职业 + 进度 */
    RECT bossline;       /* 当前 Boss / 目标 */
    RECT table;          /* 三级统计表 */
    RECT breakdown;      /* 伤害来源 */
    RECT log;            /* 事件日志面板 */
    RECT log_up, log_down;
    RECT log_chip[EVFILT_COUNT];   /* 事件日志过滤器按钮 */
    RECT history;        /* 历史翻页条 */
    RECT prev_run, next_run, prev_fight, next_fight;
    RECT footer;         /* 底部状态栏 */
    int  table_head_y;
    int  table_row_y;
    int  table_rows;
    int  row_h;
    int  bd_title_y;
    int  bd_row_y;
    int  bd_rows;
    int  bd_row_h;
    int  log_title_y;
    int  log_row_y;
    int  log_rows;
    int  log_row_h;
} HudLayout;

/* 计算布局；w/h 为窗口像素尺寸（已含缩放） */
void hud_layout(int w, int h, bool log_on, HudLayout* L);

/* 命中测试：返回 HudBtn */
int  hud_hit_test(int x, int y, const HudLayout* L);

void hud_free_fonts(void);

/* 绘制整窗。log_scroll = 事件日志向上滚动的行数（0 = 最新） */
void hud_paint(HDC dc, const HudLayout* L, const Config* cfg, const StatsView* v,
               const EvLog* ev, const char* status, const char* logsrc,
               int hover_btn, int log_scroll);

#endif
