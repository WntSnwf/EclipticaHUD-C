/* hud.c - HUD 布局 + GDI 绘制
 *
 * 坐标系：所有布局数值都在 460x620 的"逻辑单位"里，窗口通过
 * MM_ANISOTROPIC 映射把逻辑坐标等比放大到实际像素，因此字体、间距、
 * 按钮在任意缩放下都是同一套版式，不会因为缩放而互相压盖。
 *
 * 各区块的矩形全部由 hud_layout() 统一给出，绘制与命中测试共用，
 * 从结构上消除了"日志面板盖住统计行""底部提示压住翻页按钮"这类问题。
 */
#include "hud.h"
#include "zhtext.h"
#include "names.h"
#include "format.h"
#include "compat.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>

/* ---------------- 调色板 ---------------- */
#define C_BG         RGB(11, 13, 19)
#define C_PANEL      RGB(20, 25, 35)
#define C_PANEL2     RGB(26, 32, 45)
#define C_BAND       RGB(16, 20, 29)
#define C_BORDER     RGB(56, 68, 92)
#define C_BORDER_HI  RGB(110, 132, 172)
#define C_TEXT       RGB(230, 236, 246)
#define C_DIM        RGB(146, 158, 182)
#define C_FAINT      RGB(104, 114, 136)
#define C_ACCENT     RGB(118, 188, 255)
#define C_GOLD       RGB(255, 214, 120)
#define C_RED        RGB(242, 138, 116)
#define C_GREEN      RGB(132, 220, 152)
#define C_PURPLE     RGB(196, 168, 255)

/* ---------------- 逻辑版式常量 ---------------- */
#define TABLE_ROWS 9
#define ROW_H      19
#define PAD        10
#define TITLE_H    26
#define BARROW_H   27
#define HDR_H      (TITLE_H + BARROW_H + 4)
#define FOOT_H     22
#define HIST_H     26
#define LOG_H      142

/* ---------------- 字体 ---------------- */
static HFONT g_f_title, g_f_body, g_f_small;

static void ensure_fonts(void)
{
    if (g_f_title) return;
    g_f_title = CreateFontW(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, L"Microsoft YaHei");
    g_f_body  = CreateFontW(-13, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, L"Microsoft YaHei");
    g_f_small = CreateFontW(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, L"Microsoft YaHei");
}

void hud_free_fonts(void)
{
    if (g_f_title) { DeleteObject(g_f_title); g_f_title = NULL; }
    if (g_f_body)  { DeleteObject(g_f_body);  g_f_body  = NULL; }
    if (g_f_small) { DeleteObject(g_f_small); g_f_small = NULL; }
}

/* ---------------- 基础绘制 ---------------- */

static void rset(RECT* r, int l, int t, int rr, int b)
{
    r->left = l; r->top = t; r->right = rr; r->bottom = b;
}

static void fill_rect(HDC dc, const RECT* r, COLORREF c)
{
    HBRUSH b = CreateSolidBrush(c);
    FillRect(dc, r, b);
    DeleteObject(b);
}

static void frame_rect(HDC dc, const RECT* r, COLORREF c)
{
    HPEN p = CreatePen(PS_SOLID, 1, c);
    HPEN op = (HPEN)SelectObject(dc, p);
    HBRUSH ob = (HBRUSH)SelectObject(dc, GetStockObject(NULL_BRUSH));
    Rectangle(dc, r->left, r->top, r->right, r->bottom);
    SelectObject(dc, op);
    SelectObject(dc, ob);
    DeleteObject(p);
}

static void panel(HDC dc, const RECT* r, COLORREF fill, COLORREF border)
{
    fill_rect(dc, r, fill);
    frame_rect(dc, r, border);
}

static void hline(HDC dc, int x1, int x2, int y, COLORREF c)
{
    RECT r;
    rset(&r, x1, y, x2, y + 1);
    fill_rect(dc, &r, c);
}

static void vline(HDC dc, int x, int y1, int y2, COLORREF c)
{
    RECT r;
    rset(&r, x, y1, x + 1, y2);
    fill_rect(dc, &r, c);
}

static const wchar_t* wstr(const char* utf8, wchar_t* buf, int cap)
{
    if (!utf8) { buf[0] = 0; return buf; }
    if (MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, cap) <= 0) buf[0] = 0;
    return buf;
}

static int text_w(HDC dc, HFONT f, const char* utf8)
{
    wchar_t w[512];
    SIZE sz;
    wstr(utf8, w, 512);
    if (!w[0]) return 0;
    SelectObject(dc, f);
    if (!GetTextExtentPoint32W(dc, w, (int)wcslen(w), &sz)) return 0;
    return sz.cx;
}

static void text_l(HDC dc, int x, int y, HFONT f, COLORREF c, const char* utf8)
{
    wchar_t w[512];
    wstr(utf8, w, 512);
    size_t n = wcslen(w);
    if (!n) return;
    SelectObject(dc, f);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, x, y, w, (int)n);
}

static void text_r(HDC dc, int x_right, int y, HFONT f, COLORREF c, const char* utf8)
{
    wchar_t w[512];
    wstr(utf8, w, 512);
    size_t n = wcslen(w);
    if (!n) return;
    SIZE sz;
    SelectObject(dc, f);
    GetTextExtentPoint32W(dc, w, (int)n, &sz);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, x_right - sz.cx, y, w, (int)n);
}

static void text_c(HDC dc, int cx, int y, HFONT f, COLORREF c, const char* utf8)
{
    wchar_t w[512];
    wstr(utf8, w, 512);
    size_t n = wcslen(w);
    if (!n) return;
    SIZE sz;
    SelectObject(dc, f);
    GetTextExtentPoint32W(dc, w, (int)n, &sz);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, cx - sz.cx / 2, y, w, (int)n);
}

/* 按像素宽度裁剪 UTF-8 文本（保持字符边界） */
static void fit_text(HDC dc, HFONT f, char* s, int maxpx)
{
    if (maxpx <= 0) { s[0] = 0; return; }
    while (s[0] && text_w(dc, f, s) > maxpx) {
        size_t n = strlen(s);
        if (n == 0) break;
        do { n--; } while (n > 0 && ((unsigned char)s[n] & 0xC0) == 0x80);
        s[n] = 0;
    }
}

/* ---------------- 布局 ---------------- */

void hud_layout(int w, int h, bool log_on, HudLayout* L)
{
    memset(L, 0, sizeof(*L));
    L->log_on = log_on;

    rset(&L->title, 0, 0, w, TITLE_H);
    rset(&L->bar, 0, TITLE_H, w, TITLE_H + BARROW_H);

    int cs = 20;
    rset(&L->close_btn, w - PAD - cs, (TITLE_H - cs) / 2, w - PAD, (TITLE_H - cs) / 2 + cs);

    int gap = 3;
    int total = w - 2 * PAD;
    int bw = (total - gap * (HUD_BAR_BTN_N - 1)) / HUD_BAR_BTN_N;
    int bh = BARROW_H - 6;
    for (int i = 0; i < HUD_BAR_BTN_N; i++) {
        int x = PAD + i * (bw + gap);
        rset(&L->bar_btn[i], x, TITLE_H + 3, x + bw, TITLE_H + 3 + bh);
    }

    rset(&L->footer, 0, h - FOOT_H, w, h);
    rset(&L->history, 0, h - FOOT_H - HIST_H, w, h - FOOT_H);

    int hist_top = L->history.top;
    int log_top = hist_top - 6 - LOG_H;
    rset(&L->log, PAD, log_top, w - PAD, hist_top - 6);
    if (!log_on) rset(&L->log, PAD, log_top, w - PAD, log_top);   /* 空矩形 */

    int content_top = HDR_H;
    int content_bot = log_on ? (log_top - 8) : (hist_top - 6);

    rset(&L->info, PAD, content_top, w - PAD, content_top + 42);
    rset(&L->bossline, PAD, content_top + 46, w - PAD, content_top + 68);

    int ty = content_top + 74;
    L->table_head_y = ty + 1;
    L->table_row_y = ty + 20;
    L->table_rows = TABLE_ROWS;
    L->row_h = ROW_H;
    rset(&L->table, PAD, ty, w - PAD, L->table_row_y + TABLE_ROWS * ROW_H);

    int bd_top = L->table.bottom + 6;
    rset(&L->breakdown, PAD, bd_top, w - PAD, content_bot);
    L->bd_title_y = bd_top + 1;
    L->bd_row_y = bd_top + 19;
    L->bd_row_h = 17;
    int avail = content_bot - L->bd_row_y;
    L->bd_rows = avail > 0 ? avail / L->bd_row_h : 0;
    if (L->bd_rows > 14) L->bd_rows = 14;

    if (log_on) {
        L->log_title_y = L->log.top + 2;
        L->log_row_y = L->log.top + 21;
        L->log_row_h = 16;
        int la = L->log.bottom - L->log_row_y - 3;
        L->log_rows = la > 0 ? la / L->log_row_h : 1;
        if (L->log_rows < 1) L->log_rows = 1;

        rset(&L->log_up, L->log.right - 6 - 38, L->log_title_y, L->log.right - 6 - 20, L->log_title_y + 17);
        rset(&L->log_down, L->log.right - 6 - 18, L->log_title_y, L->log.right - 6, L->log_title_y + 17);

        /* 过滤器按钮：宽度固定，保证绘制与命中测试完全一致 */
        static const int CHIP_W[EVFILT_COUNT] = { 36, 36, 36, 80 };
        int fx = L->log.left + 74;
        for (int i = 0; i < EVFILT_COUNT; i++) {
            rset(&L->log_chip[i], fx, L->log_title_y, fx + CHIP_W[i], L->log_title_y + 17);
            fx += CHIP_W[i] + 4;
        }
    }

    int by = L->history.top + 4;
    int bs = HIST_H - 8;
    rset(&L->prev_run, PAD, by, PAD + bs, by + bs);
    rset(&L->next_run, PAD + bs + 2, by, PAD + 2 * bs + 2, by + bs);
    int fx = w / 2 - bs - 1;
    rset(&L->prev_fight, fx, by, fx + bs, by + bs);
    rset(&L->next_fight, fx + bs + 2, by, fx + 2 * bs + 2, by + bs);
}

static bool in_rect(const RECT* r, int x, int y)
{
    return x >= r->left && x < r->right && y >= r->top && y < r->bottom;
}

static const int BAR_ORDER[HUD_BAR_BTN_N] = {
    HUD_BTN_TOPMOST, HUD_BTN_BIGGER, HUD_BTN_SMALLER, HUD_BTN_OPAQUE,
    HUD_BTN_TRANSPARENT, HUD_BTN_PIERCE, HUD_BTN_LOG
};

int hud_hit_test(int x, int y, const HudLayout* L)
{
    if (in_rect(&L->close_btn, x, y)) return HUD_BTN_CLOSE;
    for (int i = 0; i < HUD_BAR_BTN_N; i++)
        if (in_rect(&L->bar_btn[i], x, y)) return BAR_ORDER[i];
    if (in_rect(&L->prev_run, x, y)) return HUD_BTN_PREV_RUN;
    if (in_rect(&L->next_run, x, y)) return HUD_BTN_NEXT_RUN;
    if (in_rect(&L->prev_fight, x, y)) return HUD_BTN_PREV_FIGHT;
    if (in_rect(&L->next_fight, x, y)) return HUD_BTN_NEXT_FIGHT;
    if (L->log_on && in_rect(&L->log_up, x, y)) return HUD_BTN_LOG_UP;
    if (L->log_on && in_rect(&L->log_down, x, y)) return HUD_BTN_LOG_DOWN;
    if (L->log_on) {
        for (int i = 0; i < EVFILT_COUNT; i++)
            if (in_rect(&L->log_chip[i], x, y)) return HUD_BTN_FILT_ALL + i;
    }
    return HUD_BTN_DRAG;
}

/* ---------------- 小组件 ---------------- */

static void draw_button(HDC dc, const RECT* r, const char* label,
                        bool active, bool hover, HFONT f)
{
    COLORREF fill = hover ? RGB(58, 74, 104) : (active ? RGB(40, 62, 96) : C_PANEL2);
    COLORREF edge = hover ? C_BORDER_HI : (active ? RGB(86, 140, 200) : C_BORDER);
    COLORREF tx   = active ? C_ACCENT : (hover ? C_TEXT : RGB(200, 210, 226));
    panel(dc, r, fill, edge);
    text_c(dc, (r->left + r->right) / 2, (r->top + r->bottom) / 2 - 8, f, tx, label);
}

static void draw_pager(HDC dc, const RECT* r, bool left, bool hover)
{
    panel(dc, r, hover ? RGB(58, 74, 104) : C_PANEL2, hover ? C_BORDER_HI : C_BORDER);
    HBRUSH b = CreateSolidBrush(hover ? C_TEXT : C_DIM);
    HBRUSH ob = (HBRUSH)SelectObject(dc, b);
    HPEN op = (HPEN)SelectObject(dc, GetStockObject(NULL_PEN));
    int cx = (r->left + r->right) / 2, cy = (r->top + r->bottom) / 2;
    POINT p[3];
    if (left) {
        p[0].x = cx - 3; p[0].y = cy;
        p[1].x = cx + 3; p[1].y = cy - 4;
        p[2].x = cx + 3; p[2].y = cy + 4;
    } else {
        p[0].x = cx + 3; p[0].y = cy;
        p[1].x = cx - 3; p[1].y = cy - 4;
        p[2].x = cx - 3; p[2].y = cy + 4;
    }
    Polygon(dc, p, 3);
    SelectObject(dc, op);
    SelectObject(dc, ob);
    DeleteObject(b);
}

static COLORREF kind_color(int kind)
{
    switch (kind) {
    case EVK_DAMAGE: return C_RED;
    case EVK_TARGET: return C_ACCENT;
    case EVK_BOSS:   return C_GOLD;
    case EVK_DEATH:  return C_PURPLE;
    case EVK_TOKEN:  return C_GREEN;
    default:         return RGB(200, 208, 222);
    }
}

/* ---------------- 区块：信息 ---------------- */

static void draw_info(HDC dc, const HudLayout* L, const StatsView* v)
{
    const RECT* r = &L->info;
    panel(dc, r, C_PANEL, C_BORDER);

    int x = r->left + 8, y = r->top + 3;

    char stage[96];
    if (v->stage_name && v->stage_name[0])
        snprintf_(stage, sizeof(stage), "%d · %s", v->stage_no, v->stage_name);
    else
        snprintf_(stage, sizeof(stage), "%s", TXT_NO_STAGE);

    text_l(dc, x, y, g_f_body, C_DIM, TXT_COL_STAGE);
    text_l(dc, x + text_w(dc, g_f_body, TXT_COL_STAGE) + 5, y, g_f_body,
           (v->stage_name && v->stage_name[0]) ? C_TEXT : C_FAINT, stage);

    char cls[80];
    cls[0] = 0;
    if (v->cls && v->cls[0]) snprintf_(cls, sizeof(cls), "%s %s", TXT_CLASS_LABEL, v->cls);
    text_r(dc, r->right - 8, y, g_f_small, C_DIM, cls);

    /* 进度条 */
    int by = r->top + 25;
    int bx = x, bw = 148, bh = 9;
    RECT bar;
    rset(&bar, bx, by, bx + bw, by + bh);
    fill_rect(dc, &bar, RGB(30, 36, 50));
    if (v->stage_progress > 0) {
        double p = v->stage_progress;
        if (p > 1) p = 1;
        RECT f;
        int fw = (int)((bw - 2) * p);
        if (fw < 1) fw = 1;
        rset(&f, bx + 1, by + 1, bx + 1 + fw, by + bh - 1);
        fill_rect(dc, &f, p >= 1.0 ? C_GOLD : C_ACCENT);
    }
    frame_rect(dc, &bar, C_BORDER);

    char pbuf[64];
    if (v->stage_name && v->stage_name[0])
        snprintf_(pbuf, sizeof(pbuf), "%s  %.0f%%",
                  phase_display(v->stage_progress), v->stage_progress * 100.0);
    else
        pbuf[0] = 0;
    text_l(dc, bx + bw + 8, by - 4, g_f_small, C_DIM, pbuf);

    char k[32], t[32], tk[48], sum[160];
    snprintf_(k, sizeof(k), TXT_KILLS, v->kills);
    snprintf_(t, sizeof(t), TXT_TARGETS, v->targets);
    if (v->level_tokens > 0) snprintf_(tk, sizeof(tk), TXT_TOKENS_X, v->stage_tokens, v->level_tokens);
    else snprintf_(tk, sizeof(tk), "%s %d", TXT_ROW_TOKENS, v->tokens);
    snprintf_(sum, sizeof(sum), "%s   %s   %s", k, t, tk);
    text_r(dc, r->right - 8, by - 4, g_f_small, C_DIM, sum);
}

/* ---------------- 区块：Boss 行 ---------------- */

static const char* result_text(const char* result, COLORREF* col)
{
    if (!result || !result[0]) { *col = C_DIM; return ""; }
    if (!strcmp(result, "WON"))   { *col = C_GREEN; return TXT_RESULT_WON; }
    if (!strcmp(result, "LOST"))  { *col = C_RED;   return TXT_RESULT_LOST; }
    if (!strcmp(result, "LOBBY")) { *col = C_DIM;   return TXT_RESULT_LOBBY; }
    if (!strcmp(result, "LEFT"))  { *col = C_DIM;   return TXT_RESULT_LEFT; }
    *col = C_GOLD;
    return TXT_RESULT_OPEN;
}

static void draw_bossline(HDC dc, const HudLayout* L, const StatsView* v)
{
    const RECT* r = &L->bossline;
    bool has_boss = v->boss && v->boss[0];

    char left[160], nm[96];
    if (has_boss) {
        if (v->boss_phase > 1) snprintf_(nm, sizeof(nm), "%s (P%d)", v->boss, v->boss_phase);
        else snprintf_(nm, sizeof(nm), "%s", v->boss);
        snprintf_(left, sizeof(left), TXT_FIGHT_LBL, nm);
    } else {
        snprintf_(left, sizeof(left), "%s", TXT_NO_FIGHT);
    }
    text_l(dc, r->left + 2, r->top + 2, g_f_body, has_boss ? C_GOLD : C_FAINT, left);

    int cursor = r->left + 2 + text_w(dc, g_f_body, left) + 10;

    COLORREF rcol;
    const char* rtxt = result_text(v->result, &rcol);
    if (rtxt[0]) {
        int tw = text_w(dc, g_f_small, rtxt);
        RECT pill;
        rset(&pill, cursor, r->top + 2, cursor + tw + 12, r->top + 19);
        panel(dc, &pill, RGB(28, 34, 46), rcol);
        text_c(dc, cursor + tw / 2 + 6, r->top + 3, g_f_small, rcol, rtxt);
    }

    if (has_boss) {
        char tmp[32], right[224];
        fmt_duration(tmp, sizeof(tmp), v->fight_elapsed > 0 ? v->fight_elapsed : 0);
        if (v->target && v->target[0]) {
            char t2[32];
            fmt_duration(t2, sizeof(t2), v->target_secs > 0 ? v->target_secs : 0);
            if (v->target_is_boss || !v->target_obj || !v->target_obj[0])
                snprintf_(right, sizeof(right), TXT_DURATION "   " TXT_TARGET_FOR,
                          tmp, v->target, t2);
            else
                snprintf_(right, sizeof(right), TXT_DURATION "   " TXT_TARGET_OF,
                          tmp, v->target_obj, v->target, t2);
        } else {
            snprintf_(right, sizeof(right), TXT_DURATION "   " TXT_TARGET_NONE, tmp);
        }
        text_r(dc, r->right - 2, r->top + 2, g_f_small, C_DIM, right);
    } else if (v->target && v->target[0]) {
        /* 不在 Boss 战时也汇报最近一次目标切换（覆盖杂兵/召唤物）*/
        char right[224], t2[32];
        fmt_duration(t2, sizeof(t2), v->target_secs > 0 ? v->target_secs : 0);
        snprintf_(right, sizeof(right), TXT_TARGET_OF, v->target_obj, v->target, t2);
        text_r(dc, r->right - 2, r->top + 2, g_f_small, C_DIM, right);
    }
}

/* ---------------- 区块：三级统计表 ---------------- */

enum { FMT_AMOUNT = 0, FMT_INT, FMT_RATE };

typedef struct {
    const char* label;
    int    fmt;
    double a, b, c;
    bool   has_c;
    COLORREF col;
} TableRow;

static COLORREF row_color(int row)
{
    switch (row) {
    case 1: return C_GOLD;      /* DPS */
    case 2: return C_RED;       /* 承伤 */
    case 4: return C_RED;       /* 最大受击 */
    case 6: return C_RED;       /* 承伤/秒 */
    case 7: return C_PURPLE;    /* 死亡 */
    case 8: return C_GREEN;     /* 印记 */
    default: return C_TEXT;
    }
}

static void draw_table(HDC dc, const HudLayout* L, const StatsView* v)
{
    const RECT* t = &L->table;
    int cw = (t->right - t->left) / 3;
    int cx[3];
    for (int i = 0; i < 3; i++) cx[i] = t->left + i * cw;

    /* 表头 */
    RECT hr;
    rset(&hr, t->left, t->top, t->right, t->top + 18);
    fill_rect(dc, &hr, C_PANEL2);
    {
        static const char* names[3] = { TXT_COL_STAGE, TXT_COL_RUN, TXT_COL_FIGHT };
        for (int i = 0; i < 3; i++)
            text_c(dc, cx[i] + cw / 2, t->top + 1, g_f_body, C_TEXT, names[i]);
        for (int i = 1; i < 3; i++)
            vline(dc, cx[i], t->top + 3, t->top + 15, C_BORDER);
    }

    const Agg* sg = &v->stage;
    const Agg* rn = &v->run;
    const Agg* ft = &v->fight;

    TableRow rows[TABLE_ROWS];
    memset(rows, 0, sizeof(rows));
    int i = 0;
#define ROW(lbl, f, av, bv, cv, hc) do {                    \
        rows[i].label = lbl; rows[i].fmt = f;               \
        rows[i].a = av; rows[i].b = bv; rows[i].c = cv;     \
        rows[i].has_c = hc; rows[i].col = row_color(i); i++; } while (0)

    ROW(TXT_ROW_DMG,    FMT_AMOUNT, sg->dmg, rn->dmg, ft->dmg, true);
    ROW(TXT_ROW_DPS,    FMT_RATE,   v->stage_dps, v->run_dps, v->fight_dps, true);
    ROW(TXT_ROW_TAKEN,  FMT_AMOUNT, sg->taken, rn->taken, ft->taken, true);
    ROW(TXT_ROW_HITS,   FMT_INT,    sg->hits, rn->hits, ft->hits, true);
    ROW(TXT_ROW_MAXHIT, FMT_AMOUNT, sg->max_hit, rn->max_hit, ft->max_hit, true);
    ROW(TXT_ROW_AVGHIT, FMT_AMOUNT,
        sg->hits > 0 ? sg->taken / sg->hits : 0,
        rn->hits > 0 ? rn->taken / rn->hits : 0,
        ft->hits > 0 ? ft->taken / ft->hits : 0, true);
    ROW(TXT_ROW_TPS,    FMT_RATE,   v->taken_per_sec, v->taken_per_sec, 0, false);
    ROW(TXT_ROW_DEATHS, FMT_INT,    sg->deaths, rn->deaths, ft->deaths, true);
    ROW(TXT_ROW_TOKENS, FMT_INT,    sg->tokens, rn->tokens, 0, false);
#undef ROW

    char buf[64];
    for (int k = 0; k < TABLE_ROWS; k++) {
        int y = L->table_row_y + k * L->row_h;
        RECT rr;
        rset(&rr, t->left + 1, y, t->right - 1, y + L->row_h - 1);
        fill_rect(dc, &rr, (k & 1) ? C_BAND : C_PANEL);
        text_l(dc, t->left + 7, y + 2, g_f_small, C_DIM, rows[k].label);
        for (int c = 0; c < 3; c++) {
            bool ok = (c < 2) || rows[k].has_c;
            if (!ok) { snprintf_(buf, sizeof(buf), "–"); }
            else {
                double val = c == 0 ? rows[k].a : (c == 1 ? rows[k].b : rows[k].c);
                if (rows[k].fmt == FMT_INT) snprintf_(buf, sizeof(buf), "%d", (int)(val + 0.5));
                else if (rows[k].fmt == FMT_RATE) fmt_rate(buf, sizeof(buf), val);
                else fmt_amount(buf, sizeof(buf), val);
            }
            text_r(dc, cx[c] + cw - 7, y + 2, g_f_body, rows[k].col, buf);
        }
        hline(dc, t->left + 1, t->right - 1, y + L->row_h - 1, RGB(32, 38, 52));
    }
    frame_rect(dc, t, C_BORDER);
}

/* ---------------- 区块：伤害来源 ---------------- */

static void draw_breakdown(HDC dc, const HudLayout* L, const StatsView* v)
{
    const RECT* r = &L->breakdown;
    if (r->bottom - r->top < 34) return;
    panel(dc, r, C_PANEL, C_BORDER);

    const char* scope = v->attacks_scope == 0 ? TXT_BD_FIGHT
                      : (v->attacks_scope == 1 ? TXT_BD_STAGE : TXT_BD_RUN);
    char title[96];
    snprintf_(title, sizeof(title), "%s%s", TXT_BREAKDOWN, scope);
    text_l(dc, r->left + 6, L->bd_title_y, g_f_body, C_TEXT, title);

    if (v->n_attacks == 0) {
        text_l(dc, r->left + 6, L->bd_row_y + 2, g_f_small, C_FAINT, TXT_BD_NONE);
        return;
    }
    {
        char cbuf[32];
        snprintf_(cbuf, sizeof(cbuf), "%d", v->n_attacks);
        text_r(dc, r->right - 6, L->bd_title_y, g_f_small, C_FAINT, cbuf);
    }

    for (int i = 0; i < L->bd_rows && i < v->n_attacks; i++) {
        const Tally* t = &v->attacks[i];
        int y = L->bd_row_y + i * L->bd_row_h;

        char amt[40], hits[24], who[128];
        fmt_amount(amt, sizeof(amt), t->total);
        snprintf_(hits, sizeof(hits), "x%d", t->hits);
        if (t->attack[0]) snprintf_(who, sizeof(who), "%s · %s", t->who, t->attack);
        else snprintf_(who, sizeof(who), "%s", t->who);

        int hw = text_w(dc, g_f_small, hits);
        int aw = text_w(dc, g_f_body, amt);
        int avail = (r->right - 12) - (r->left + 6) - hw - aw - 14;
        fit_text(dc, g_f_small, who, avail);

        text_l(dc, r->left + 6, y, g_f_small, C_DIM, who);
        text_r(dc, r->right - 6 - hw - 6, y, g_f_body, C_RED, amt);
        text_r(dc, r->right - 6, y, g_f_small, C_FAINT, hits);
    }
}

/* ---------------- 区块：历史翻页 ---------------- */

static void draw_history(HDC dc, const HudLayout* L, const StatsView* v, int hover)
{
    const RECT* r = &L->history;
    fill_rect(dc, r, C_PANEL);
    hline(dc, 0, r->right, r->top, C_BORDER);

    draw_pager(dc, &L->prev_run, true, hover == HUD_BTN_PREV_RUN);
    draw_pager(dc, &L->next_run, false, hover == HUD_BTN_NEXT_RUN);
    draw_pager(dc, &L->prev_fight, true, hover == HUD_BTN_PREV_FIGHT);
    draw_pager(dc, &L->next_fight, false, hover == HUD_BTN_NEXT_FIGHT);

    int total_run = v->run_count + (v->live ? 1 : 0);
    if (total_run < 1) total_run = 1;
    char buf[64];
    snprintf_(buf, sizeof(buf), TXT_RUN_PAGE, v->run_number, total_run);
    text_l(dc, L->next_run.right + 8, r->top + 5, g_f_small, C_TEXT, buf);

    if (v->fight_count > 0) {
        int fcur = v->view_fight_index < 0 ? v->fight_count : v->view_fight_index + 1;
        snprintf_(buf, sizeof(buf), TXT_FIGHT_PAGE, fcur, v->fight_count);
        text_l(dc, L->next_fight.right + 8, r->top + 5, g_f_small, C_TEXT, buf);
    }

    bool hist = !v->live;
    const char* statetxt = hist ? TXT_HISTORY : TXT_LIVE;
    COLORREF col = hist ? C_GOLD : C_GREEN;
    int w = text_w(dc, g_f_small, statetxt);
    RECT pill;
    rset(&pill, r->right - PAD - w - 14, r->top + 4, r->right - PAD, r->bottom - 4);
    panel(dc, &pill, hist ? RGB(46, 38, 20) : RGB(20, 40, 28),
          hist ? RGB(130, 104, 50) : RGB(58, 118, 78));
    text_c(dc, (pill.left + pill.right) / 2, r->top + 5, g_f_small, col, statetxt);
}

/* ---------------- 区块：底部 / 事件日志 ---------------- */

static void draw_footer(HDC dc, const HudLayout* L, const char* status, const char* src)
{
    const RECT* r = &L->footer;
    fill_rect(dc, r, RGB(17, 21, 30));
    hline(dc, 0, r->right, r->top, C_BORDER);
    text_l(dc, PAD, r->top + 3, g_f_small, C_TEXT, status ? status : "");
    if (src && src[0]) text_r(dc, r->right - PAD, r->top + 3, g_f_small, C_FAINT, src);
}

static void draw_log(HDC dc, const HudLayout* L, const EvLog* ev, int filter,
                     int scroll, int hover)
{
    const RECT* r = &L->log;
    panel(dc, r, RGB(14, 17, 24), C_BORDER);

    text_l(dc, r->left + 6, L->log_title_y, g_f_body, C_TEXT, TXT_EVENT_LOG);

    static const char* filters[EVFILT_COUNT] = {
        TXT_FILTER_ALL, TXT_FILTER_DMG, TXT_FILTER_TGT, TXT_FILTER_BOSS
    };
    for (int i = 0; i < EVFILT_COUNT; i++) {
        const RECT* chip = &L->log_chip[i];
        bool on = (i == filter);
        bool hov = (hover == HUD_BTN_FILT_ALL + i);
        COLORREF fill = on ? RGB(40, 62, 96) : (hov ? RGB(48, 60, 82) : C_PANEL2);
        COLORREF edge = on ? C_ACCENT : (hov ? C_BORDER_HI : C_BORDER);
        COLORREF tx = on ? C_ACCENT : (hov ? C_TEXT : C_DIM);
        panel(dc, chip, fill, edge);
        text_c(dc, (chip->left + chip->right) / 2, L->log_title_y + 1, g_f_small, tx, filters[i]);
    }

    draw_button(dc, &L->log_down, "▼", false, hover == HUD_BTN_LOG_DOWN, g_f_small);
    draw_button(dc, &L->log_up, "▲", false, hover == HUD_BTN_LOG_UP, g_f_small);

    int shown = 0, skip = scroll;
    for (int idx = 0; idx < evlog_count(ev) && shown < L->log_rows; idx++) {
        const EvEntry* e = evlog_at(ev, idx);
        if (!e || !evlog_filter_match(e->kind, filter)) continue;
        if (skip > 0) { skip--; continue; }
        char t[16], line[EVLOG_TEXT + 32];
        fmt_clock(t, sizeof(t), e->t);
        snprintf_(line, sizeof(line), "%s  %s", t, e->text);
        text_l(dc, r->left + 6, L->log_row_y + shown * L->log_row_h, g_f_small,
               kind_color(e->kind), line);
        shown++;
    }
    if (shown == 0)
        text_l(dc, r->left + 6, L->log_row_y, g_f_small, C_FAINT, TXT_LOG_EMPTY);
}

/* 按钮提示文本：悬停时显示在底部状态栏右侧，不遮挡任何数据 */
static const char* button_tip(int hover)
{
    switch (hover) {
    case HUD_BTN_TOPMOST:     return TXT_TIP_TOP;
    case HUD_BTN_BIGGER:      return TXT_TIP_BIGGER;
    case HUD_BTN_SMALLER:     return TXT_TIP_SMALLER;
    case HUD_BTN_OPAQUE:      return TXT_TIP_OPAQUE;
    case HUD_BTN_TRANSPARENT: return TXT_TIP_FADED;
    case HUD_BTN_PIERCE:      return TXT_TIP_PIERCE;
    case HUD_BTN_LOG:         return TXT_TIP_LOG;
    case HUD_BTN_CLOSE:       return TXT_TIP_CLOSE;
    case HUD_BTN_PREV_RUN:    return TXT_TIP_PREV_RUN;
    case HUD_BTN_NEXT_RUN:    return TXT_TIP_NEXT_RUN;
    case HUD_BTN_PREV_FIGHT:  return TXT_TIP_PREV_FIGHT;
    case HUD_BTN_NEXT_FIGHT:  return TXT_TIP_NEXT_FIGHT;
    case HUD_BTN_LOG_UP:      return TXT_TIP_LOG_UP;
    case HUD_BTN_LOG_DOWN:    return TXT_TIP_LOG_DOWN;
    case HUD_BTN_FILT_ALL:    return TXT_TIP_FILT_ALL;
    case HUD_BTN_FILT_DAMAGE: return TXT_TIP_FILT_DMG;
    case HUD_BTN_FILT_TARGET: return TXT_TIP_FILT_TGT;
    case HUD_BTN_FILT_BOSS:   return TXT_TIP_FILT_BOSS;
    default:                  return NULL;
    }
}

/* ---------------- 主绘制 ---------------- */

void hud_paint(HDC dc, const HudLayout* L, const Config* cfg, const StatsView* v,
               const EvLog* ev, const char* status, const char* logsrc,
               int hover_btn, int log_scroll)
{
    ensure_fonts();

    int w = L->footer.right;
    int h = L->footer.bottom;

    RECT all;
    rset(&all, 0, 0, w, h);
    fill_rect(dc, &all, C_BG);
    frame_rect(dc, &all, C_BORDER_HI);

    /* 标题行 */
    RECT tr;
    rset(&tr, 1, 1, w - 1, TITLE_H);
    fill_rect(dc, &tr, RGB(23, 29, 41));
    {
        RECT dot;
        rset(&dot, PAD, 10, PAD + 7, 17);
        fill_rect(dc, &dot, C_ACCENT);
        text_l(dc, PAD + 13, 4, g_f_title, C_TEXT, TXT_APP_TITLE);
        int tw = text_w(dc, g_f_title, TXT_APP_TITLE);
        text_l(dc, PAD + 19 + tw, 7, g_f_small, C_FAINT, TXT_APP_SUB);
        /* 鼠标穿透开启时窗口收不到任何鼠标事件，必须在标题栏常驻提示怎么恢复 */
        if (cfg->click_through)
            text_r(dc, L->close_btn.left - 8, 7, g_f_small, C_GOLD, TXT_PIERCE_BADGE);
        draw_button(dc, &L->close_btn, TXT_BTN_CLOSE, false,
                    hover_btn == HUD_BTN_CLOSE, g_f_body);
    }

    /* 按钮行 */
    RECT br;
    rset(&br, 1, TITLE_H, w - 1, TITLE_H + BARROW_H);
    fill_rect(dc, &br, C_PANEL);
    {
        static const char* labels[HUD_BAR_BTN_N] = {
            TXT_BTN_TOP, TXT_BTN_BIGGER, TXT_BTN_SMALLER, TXT_BTN_OPAQUE,
            TXT_BTN_FADED, TXT_BTN_PIERCE, TXT_BTN_LOG
        };
        for (int i = 0; i < HUD_BAR_BTN_N; i++) {
            bool active = false;
            if (BAR_ORDER[i] == HUD_BTN_TOPMOST) active = cfg->always_on_top;
            if (BAR_ORDER[i] == HUD_BTN_LOG) active = cfg->show_event_log;
            if (BAR_ORDER[i] == HUD_BTN_PIERCE) active = cfg->click_through;
            draw_button(dc, &L->bar_btn[i], labels[i], active,
                        hover_btn == BAR_ORDER[i], g_f_body);
        }
    }
    hline(dc, 1, w - 1, TITLE_H + BARROW_H, C_BORDER);

    /* 内容 */
    draw_info(dc, L, v);
    draw_bossline(dc, L, v);
    draw_table(dc, L, v);
    draw_breakdown(dc, L, v);
    if (cfg->show_event_log && L->log_on)
        draw_log(dc, L, ev, cfg->ev_filter, log_scroll, hover_btn);
    draw_history(dc, L, v, hover_btn);

    const char* tip = button_tip(hover_btn);
    draw_footer(dc, L, status, tip ? tip : logsrc);
}
