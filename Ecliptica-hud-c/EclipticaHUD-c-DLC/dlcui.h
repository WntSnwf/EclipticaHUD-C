/* dlcui.h - DLC 面板的版式计算与 GDI 绘制
 *
 * 与本体一样：版式全部由 dlcui_layout() 一次算出，绘制与命中测试共用同一份
 * 矩形，从结构上避免"按钮点不到 / 互相压盖"。
 */
#ifndef DLCUI_H
#define DLCUI_H

#include <windows.h>
#include "res.h"

/* 逻辑坐标画布尺寸（实际窗口按 DPI / 缩放放大）*/
#define DLC_W 260
#define DLC_H 212

typedef struct {
    RECT title;        /* 标题行 */
    RECT boss;         /* 当前 Boss 行 */
    RECT body;         /* 元素表 / 说明文字区 */
    RECT foot;         /* 底部状态行 */
    RECT close_btn;    /* 右上关闭按钮 */
    int  row_y;        /* 第一行的 y */
    int  row_h;        /* 行高 */
    int  rows;         /* 可容纳的行数 */
} DlcLayout;

/* 视图：把"要画什么"和"数据源"解耦，preview 工具可以直接喂假数据 */
typedef struct {
    const char* boss_display;   /* 当前 Boss 名（沿用数据表里的英文名）；空串 = 没有 Boss 战 */
    int         phase;          /* 形态号，>1 时在名字后标注 */
    bool        in_fight;
    const BossRes* res;         /* 查到的抗性条目；NULL = 没数据 */
    bool        table_ok;       /* 抗性表本身读到了没有（没读到 = 要提示用户去放）*/
    const char* table_dir;      /* 读不到表时，建议把它放到哪个目录 */
    const char* status;         /* 底部状态文字 */
    const char* logname;        /* 右下角日志名 */
} DlcView;

void dlcui_layout(DlcLayout* L);

/* 命中测试：返回 "close" 或 ""（空白处 = 可拖动）*/
const char* dlcui_hit(const DlcLayout* L, int x, int y);

/* 绘制到 dc（dc 处于 MM_ANISOTROPIC 逻辑坐标映射下）*/
void dlcui_paint(HDC dc, const DlcLayout* L, const DlcView* v, int hover_close, double blink);

void dlcui_free_fonts(void);

#endif
