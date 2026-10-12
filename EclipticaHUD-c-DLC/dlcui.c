/* dlcui.c - DLC 面板绘制 */
#include "dlcui.h"
#include "uitext.h"
#include "compat.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>

/* ---------------- 配色（与本体同色系）---------------- */
#define C_BG        RGB(11, 13, 19)
#define C_PANEL     RGB(20, 25, 35)
#define C_PANEL2    RGB(26, 32, 45)
#define C_BORDER    RGB(56, 68, 92)
#define C_BORDER_HI RGB(110, 132, 172)
#define C_TEXT      RGB(230, 236, 246)
#define C_DIM       RGB(146, 158, 182)
#define C_FAINT     RGB(104, 114, 136)
#define C_ACCENT    RGB(118, 188, 255)
/* 弱 = 暖色（打上去更疼），抗 = 冷色（打上去更少）*/
#define C_WEAK      RGB(255, 150, 120)
#define C_RESIST    RGB(120, 176, 255)
#define C_NEUTRAL   RGB(150, 162, 186)
#define C_WARN      RGB(240, 200, 110)

#define PAD 8

/* ---------------- 字体 ---------------- */
static HFONT g_f_title, g_f_body, g_f_small;

/* 元素名是英文（与数据文件一致），界面文字是中文，所以需要中日文兜底 */
static const wchar_t* const FACES[] = {
    L"Microsoft YaHei", L"Meiryo UI", L"MS UI Gothic", L"SimSun",
    L"Segoe UI", L"Tahoma"
};

static int CALLBACK enum_cb(const LOGFONTW* lf, const TEXTMETRICW* tm, DWORD t, LPARAM lp)
{
    (void)lf; (void)tm; (void)t;
    *(int*)lp = 1;
    return 0;
}

static bool face_ok(HDC dc, const wchar_t* face)
{
    LOGFONTW lf;
    int found = 0;
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = DEFAULT_CHARSET;
    wcsncpy(lf.lfFaceName, face, LF_FACESIZE - 1);
    EnumFontFamiliesExW(dc, &lf, enum_cb, (LPARAM)&found, 0);
    return found != 0;
}

static const wchar_t* pick_face(void)
{
    HDC dc = GetDC(NULL);
    if (!dc) return FACES[0];
    const wchar_t* face = FACES[0];
    for (size_t i = 0; i < sizeof(FACES) / sizeof(FACES[0]); i++) {
        if (face_ok(dc, FACES[i])) { face = FACES[i]; break; }
    }
    ReleaseDC(NULL, dc);
    return face;
}

static void ensure_fonts(void)
{
    if (g_f_title) return;
    const wchar_t* face = pick_face();
    g_f_title = CreateFontW(-14, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, face);
    g_f_body  = CreateFontW(-13, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, face);
    g_f_small = CreateFontW(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, face);
}

void dlcui_free_fonts(void)
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

static void fill(HDC dc, const RECT* r, COLORREF c)
{
    HBRUSH b = CreateSolidBrush(c);
    FillRect(dc, r, b);
    DeleteObject(b);
}

static void frame(HDC dc, const RECT* r, COLORREF c)
{
    HBRUSH b = CreateSolidBrush(c);
    FrameRect(dc, r, b);
    DeleteObject(b);
}

static const wchar_t* wstr(const char* utf8, wchar_t* buf, int cap)
{
    if (!utf8) { buf[0] = 0; return buf; }
    if (MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, cap) <= 0) buf[0] = 0;
    return buf;
}

static int tw(HDC dc, HFONT f, const char* utf8)
{
    wchar_t w[512];
    SIZE sz;
    wstr(utf8, w, 512);
    if (!w[0]) return 0;
    SelectObject(dc, f);
    if (!GetTextExtentPoint32W(dc, w, (int)wcslen(w), &sz)) return 0;
    return sz.cx;
}

static void tx(HDC dc, int x, int y, HFONT f, COLORREF c, const char* utf8)
{
    wchar_t w[512];
    wstr(utf8, w, 512);
    if (!w[0]) return;
    SelectObject(dc, f);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, x, y, w, (int)wcslen(w));
}

static void txr(HDC dc, int xr, int y, HFONT f, COLORREF c, const char* utf8)
{
    tx(dc, xr - tw(dc, f, utf8), y, f, c, utf8);
}

/* 按像素宽度裁剪（保持字符边界，不会切出半个汉字）*/
static void fit(HDC dc, HFONT f, char* s, int maxpx)
{
    if (maxpx <= 0) { s[0] = 0; return; }
    while (s[0] && tw(dc, f, s) > maxpx) {
        size_t n = strlen(s);
        if (!n) break;
        do { n--; } while (n > 0 && ((unsigned char)s[n] & 0xC0) == 0x80);
        s[n] = 0;
    }
}

/* 裁路径专用：太长时**砍掉开头**保留结尾（结尾那段目录名才是有用的），
 * 并在前面加省略号。fit() 是砍尾，对路径正好把关键信息砍掉了。 */
static void fit_path(HDC dc, HFONT f, char* s, int maxpx)
{
    if (maxpx <= 0) { s[0] = 0; return; }
    if (tw(dc, f, s) <= maxpx) return;
    static const char* ELL = "…";
    size_t n = strlen(s);
    while (n > 0) {
        /* 从开头丢掉一个 UTF-8 字符 */
        size_t step = 1;
        unsigned char c = (unsigned char)s[0];
        if (c >= 0xF0) step = 4; else if (c >= 0xE0) step = 3;
        else if (c >= 0xC0) step = 2;
        if (step > n) step = n;
        memmove(s, s + step, n - step + 1);
        n -= step;
        char tmp[256];
        snprintf(tmp, sizeof(tmp), "%s%s", ELL, s);
        if (tw(dc, f, tmp) <= maxpx) { snprintf(s, n + 1, "%s", tmp); return; }
    }
    snprintf(s, 4, "%s", ELL);
}

/* 把长文本按宽度折行写入 out（最多 max_lines 行），返回实际行数 */
static int wrap(HDC dc, HFONT f, const char* text, int maxpx, char out[][160], int max_lines)
{
    int lines = 0;
    char buf[512];
    snprintf(buf, sizeof(buf), "%s", text);
    char* p = buf;
    while (*p && lines < max_lines) {
        /* 从整段里切出能放进 maxpx 的最长前缀（按 UTF-8 字符切）*/
        char line[160];
        size_t take = 0, last_space = 0;
        size_t len = strlen(p);
        for (size_t i = 0; i < len && i < sizeof(line) - 1; ) {
            /* 前进一个 UTF-8 字符 */
            size_t step = 1;
            unsigned char c = (unsigned char)p[i];
            if (c >= 0xF0) step = 4; else if (c >= 0xE0) step = 3;
            else if (c >= 0xC0) step = 2;
            if (i + step > len) step = 1;
            memcpy(line, p, i + step);
            line[i + step] = 0;
            if (tw(dc, f, line) > maxpx) break;
            take = i + step;
            if (p[i] == ' ') last_space = take;
            i += step;
        }
        if (take == 0) take = 1;                 /* 单个字符也放不下时硬放一个 */
        else if (last_space > 0 && take < strlen(p)) take = last_space;
        snprintf(line, sizeof(line), "%.*s", (int)take, p);
        /* 去掉行尾空格 */
        size_t ln = strlen(line);
        while (ln > 0 && line[ln - 1] == ' ') line[--ln] = 0;
        snprintf(out[lines], 160, "%s", line);
        lines++;
        p += take;
        while (*p == ' ') p++;
    }
    return lines;
}

/* ---------------- 版式 ---------------- */

void dlcui_layout(DlcLayout* L)
{
    memset(L, 0, sizeof(*L));
    rset(&L->title, 0, 0, DLC_W, 24);
    rset(&L->close_btn, DLC_W - 22, 4, DLC_W - 6, 20);
    rset(&L->boss, 0, 24, DLC_W, 48);
    rset(&L->body, 0, 48, DLC_W, DLC_H - 22);
    rset(&L->foot, 0, DLC_H - 22, DLC_W, DLC_H);
    L->row_y = 52;
    L->row_h = 19;
    L->rows = (L->body.bottom - L->row_y - 2) / L->row_h;
    if (L->rows < 1) L->rows = 1;
}

const char* dlcui_hit(const DlcLayout* L, int x, int y)
{
    if (x >= L->close_btn.left && x < L->close_btn.right &&
        y >= L->close_btn.top && y < L->close_btn.bottom) return "close";
    return "";
}

/* ---------------- 绘制 ---------------- */

static void draw_button(HDC dc, const RECT* r, const char* label, bool hover)
{
    fill(dc, r, hover ? RGB(58, 74, 104) : C_PANEL2);
    frame(dc, r, hover ? C_BORDER_HI : C_BORDER);
    tx(dc, (r->left + r->right) / 2 - tw(dc, g_f_body, label) / 2, r->top + 1,
       g_f_body, C_DIM, label);
}

/* 一行元素：名字 + 倍率 + 弱/抗标记 */
static void draw_row(HDC dc, int y, int elem, const ElemVal* v, double others, bool has_others)
{
    char val[48];
    COLORREF col = C_NEUTRAL;
    const char* mark = "";
    int verdict = 0;

    const ElemVal* use = v;
    ElemVal others_v;
    memset(&others_v, 0, sizeof(others_v));
    others_v.kind = VAL_NUM;
    others_v.mult = others;
    if (use->kind == VAL_NONE && has_others) use = &others_v;

    switch (use->kind) {
    case VAL_NUM:
        verdict = res_verdict(use->mult);
        /* 1.00 -> 1x，0.50 -> 0.5x，1.25 原样。
         * （早先的写法把小数点换成 'x' 再截断，0.50x 会变成 0x —— 已修正）*/
        snprintf(val, sizeof(val), "%.2f", use->mult);
        {
            size_t n = strlen(val);
            while (n > 0 && val[n - 1] == '0') val[--n] = 0;
            if (n > 0 && val[n - 1] == '.') val[--n] = 0;
            if (n + 2 <= sizeof(val)) { val[n] = 'x'; val[n + 1] = 0; }
        }
        col = verdict > 0 ? C_WEAK : (verdict < 0 ? C_RESIST : C_NEUTRAL);
        mark = verdict > 0 ? TXT_MARK_WEAK : (verdict < 0 ? TXT_MARK_RESIST : "");
        break;
    case VAL_WEAK:
        snprintf(val, sizeof(val), "%s", TXT_VAL_WEAK);
        col = C_WEAK; mark = "▲"; verdict = 1;
        break;
    case VAL_RESIST:
        snprintf(val, sizeof(val), "%s", TXT_VAL_RESIST);
        col = C_RESIST; mark = "▼"; verdict = -1;
        break;
    default:
        snprintf(val, sizeof(val), "—");
        col = C_FAINT;
        break;
    }

    tx(dc, PAD + 2, y, g_f_small, C_DIM, res_elem_name(elem));

    int mw = tw(dc, g_f_small, mark);
    txr(dc, DLC_W - PAD - 2, y, g_f_small, verdict ? col : C_FAINT, val);
    if (mark[0]) txr(dc, DLC_W - PAD - 2 - tw(dc, g_f_body, val) - 8, y, g_f_small, col, mark);

    (void)mw;
}

/* 画说明文字：**按数据文件里的原始行**逐行输出，
 * 只有当某一行本身超过可用宽度时才把它折行；
 * 折行出来的续行缩进一点，避免和"新的一行"混在一起。 */
static void draw_note(HDC dc, const DlcLayout* L, const char* const* lines, int n_lines)
{
    int y = L->row_y;
    int maxpx = DLC_W - PAD * 2 - 14;
    for (int i = 0; i < n_lines; i++) {
        if (y + 12 > L->body.bottom) break;         /* 放不下了就停 */
        char seg[6][160];
        int n = wrap(dc, g_f_small, lines[i], maxpx, seg, 6);
        for (int k = 0; k < n; k++) {
            if (y + 12 > L->body.bottom) break;
            tx(dc, PAD + 2 + (k > 0 ? 9 : 0), y, g_f_small, C_DIM, seg[k]);
            y += 16;
        }
    }
}

void dlcui_paint(HDC dc, const DlcLayout* L, const DlcView* v, int hover_close, double blink)
{
    ensure_fonts();

    /* 底板 */
    {
        RECT all;
        rset(&all, 0, 0, DLC_W, DLC_H);
        fill(dc, &all, C_BG);
        frame(dc, &all, C_BORDER);
    }

    /* 标题行 */
    {
        RECT r = L->title;
        fill(dc, &r, C_PANEL);
        RECT dot;
        rset(&dot, PAD, 9, PAD + 7, 16);
        fill(dc, &dot, C_ACCENT);
        tx(dc, PAD + 12, 4, g_f_title, C_TEXT, "Ecliptica");
        int w = tw(dc, g_f_title, "Ecliptica");
        tx(dc, PAD + 17 + w, 7, g_f_small, C_FAINT, TXT_SUBTITLE);
        draw_button(dc, &L->close_btn, "✕", hover_close);
    }

    /* Boss 行 */
    {
        RECT r = L->boss;
        fill(dc, &r, C_PANEL2);
        char left[128];
        if (v->in_fight && v->boss_display && v->boss_display[0]) {
            /* 形态沿用 P1 / P2 的写法；Boss 名是专有名词，保持原样 */
            if (v->phase > 1)
                snprintf(left, sizeof(left), "%s  %s (P%d)", TXT_BOSS_LBL, v->boss_display, v->phase);
            else
                snprintf(left, sizeof(left), "%s  %s", TXT_BOSS_LBL, v->boss_display);
            fit(dc, g_f_body, left, DLC_W - PAD * 2 - 2);
        } else {
            snprintf(left, sizeof(left), "%s  —", TXT_BOSS_LBL);
        }
        tx(dc, PAD, r.top + 5, g_f_body,
           (v->in_fight && v->boss_display && v->boss_display[0]) ? C_TEXT : C_FAINT, left);
    }

    /* 主体 */
    {
        RECT r = L->body;
        fill(dc, &r, C_BG);

        if (!v->in_fight || !v->boss_display || !v->boss_display[0]) {
            char lines[4][160];
            int n = wrap(dc, g_f_body, TXT_WAITING, DLC_W - PAD * 2, lines, 4);
            int y = L->row_y + 20;
            for (int i = 0; i < n; i++) {
                tx(dc, (DLC_W - tw(dc, g_f_body, lines[i])) / 2, y, g_f_body, C_FAINT, lines[i]);
                y += 18;
            }
        } else if (!v->table_ok) {
            /* 表根本没读到 —— 这和"表里没有这只 Boss"是两回事，要分开提示，
             * 并且告诉用户该把文件放到哪儿。 */
            int y = L->row_y;
            tx(dc, PAD + 2, y, g_f_body, C_WARN, TXT_NO_TABLE_BODY);
            y += 20;
            tx(dc, PAD + 2, y, g_f_small, C_DIM, TXT_NO_TABLE_PUT);
            y += 16;
            if (v->table_dir && v->table_dir[0]) {
                char path[256];
                snprintf(path, sizeof(path), "%s", v->table_dir);
                fit_path(dc, g_f_small, path, DLC_W - PAD * 2 - 12);
                tx(dc, PAD + 8, y, g_f_small, C_ACCENT, path);
                y += 18;
            }
            tx(dc, PAD + 2, y, g_f_small, C_FAINT, TXT_NO_TABLE_OR);
        } else if (!v->res) {
            tx(dc, PAD + 2, L->row_y + 6, g_f_body, C_WARN, TXT_NO_DATA);
            tx(dc, PAD + 2, L->row_y + 26, g_f_small, C_FAINT, TXT_NO_DATA_HINT);
        } else if (v->res->is_note && !v->res->has_others) {
            /* 只有说明文字的条目（NaN / Jim C. Bringer(P1) 之类）*/
            bool any_num = false;
            for (int i = 0; i < ELEM_COUNT; i++)
                if (v->res->v[i].kind != VAL_NONE) any_num = true;
            if (any_num) {
                for (int i = 0; i < ELEM_COUNT && i < L->rows; i++)
                    draw_row(dc, L->row_y + i * L->row_h, i, &v->res->v[i],
                             v->res->others, v->res->has_others);
            } else {
                const char* nl[RES_NOTE_LINES];
                for (int i = 0; i < v->res->n_note; i++) nl[i] = v->res->note[i];
                draw_note(dc, L, nl, v->res->n_note);
            }
        } else {
            for (int i = 0; i < ELEM_COUNT && i < L->rows; i++)
                draw_row(dc, L->row_y + i * L->row_h, i, &v->res->v[i],
                         v->res->others, v->res->has_others);
            /* 有数值又带说明的段：底部挤一行提示 */
            if (v->res->n_note > 0) {
                int y = L->row_y + ELEM_COUNT * L->row_h + 2;
                if (y < L->body.bottom - 14) {
                    char one[160];
                    snprintf(one, sizeof(one), "%s", v->res->note[0]);
                    fit(dc, g_f_small, one, DLC_W - PAD * 2 - 4);
                    tx(dc, PAD + 2, y, g_f_small, C_WARN, one);
                }
            }
        }
    }

    /* 底部状态栏 */
    {
        RECT r = L->foot;
        fill(dc, &r, C_PANEL);
        const char* s = v->status ? v->status : "";
        /* 日志名太长时让位给状态文字 */
        char st[192];
        snprintf(st, sizeof(st), "%s", s);
        int avail = DLC_W - PAD * 2;
        if (v->logname && v->logname[0]) {
            char lg[80];
            snprintf(lg, sizeof(lg), "%s", v->logname);
            fit(dc, g_f_small, lg, 108);
            int lw = tw(dc, g_f_small, lg);
            if (lw > 0) txr(dc, DLC_W - PAD, r.top + 5, g_f_small, C_FAINT, lg);
            avail = DLC_W - PAD * 2 - lw - 8;
        }
        fit(dc, g_f_small, st, avail);
        tx(dc, PAD, r.top + 5, g_f_small, C_DIM, st);
    }

    (void)blink;
}
