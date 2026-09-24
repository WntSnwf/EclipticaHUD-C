/* overlay.c - 覆盖层窗口：日志轮询 -> 统计 -> GDI 绘制
 *
 * 渲染：Win32 + GDI 双缓冲（DIB section）+ WS_EX_LAYERED 整体不透明度。
 * 缩放：内存 DC 用 MM_ANISOTROPIC 把 460x620 的逻辑坐标等比映射到窗口
 *       像素，因此版式在任意缩放下完全一致；BitBlt 前把映射复位成
 *       MM_TEXT，避免源矩形被二次缩放。
 * 交互：拖动移动、按钮、事件日志过滤/滚动、Ctrl+Alt+Q 全局退出。
 */
#include "overlay.h"
#include "hud.h"
#include "stats.h"
#include "evlog.h"
#include "vlog.h"
#include "parse.h"
#include "evtext.h"
#include "zhtext.h"
#include "format.h"
#include "names.h"
#include "compat.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define TIMER_POLL    100
#define HOTKEY_QUIT   1
#define HOTKEY_PIERCE 2

/* 老版 MinGW 头文件缺少这些定义 */
#ifndef MOD_NOREPEAT
#define MOD_NOREPEAT 0x4000
#endif
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif
#ifndef HTTRANSPARENT
#define HTTRANSPARENT (-1)
#endif
#define HOTKEY_ID_MOD (MOD_CONTROL | MOD_ALT | MOD_NOREPEAT)

static HWND     g_hwnd;
static Config*  g_cfg;
static bool     g_demo;
static Stats    g_stats;
static EvLog    g_evlog;
static VLog*    g_vlog;

static HDC      g_memdc;
static HBITMAP  g_membmp;
static int      g_w = HUD_BASE_W;
static int      g_h = HUD_BASE_H;

static bool     g_dragging;
static POINT    g_drag_pt;
static int      g_hover = HUD_BTN_NONE;
static bool     g_tracking;
static int      g_log_scroll;

static HudLayout g_layout;
static char     g_status[192];
static char     g_logname[96];
static RECT     g_last_rect;
static double   g_dpi_scale = 1.0;
static wchar_t  g_forced_log[MAX_PATH];

/* 声明 DPI 感知，否则系统会把窗口位图拉伸，在高 DPI 屏上界面发虚、
 * 而且 GetWindowRect 与实际屏幕像素不一致。 */
static void init_dpi(void)
{
    typedef BOOL (WINAPI *PFN_SetCtx)(HANDLE);
    typedef BOOL (WINAPI *PFN_SetAware)(void);
    BOOL ok = FALSE;
    HMODULE u32 = GetModuleHandleW(L"user32.dll");
    if (u32) {
        void* raw = (void*)GetProcAddress(u32, "SetProcessDpiAwarenessContext");
        if (raw) {
            PFN_SetCtx f;
            memcpy(&f, &raw, sizeof(f));
            ok = f((HANDLE)(INT_PTR)-4);          /* PER_MONITOR_AWARE_V2 */
            if (!ok) ok = f((HANDLE)(INT_PTR)-3); /* PER_MONITOR_AWARE */
        }
        if (!ok) {
            void* raw2 = (void*)GetProcAddress(u32, "SetProcessDPIAware");
            if (raw2) {
                PFN_SetAware f2;
                memcpy(&f2, &raw2, sizeof(f2));
                ok = f2();
            }
        }
    }

    HDC dc = GetDC(NULL);
    int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : 96;
    if (dc) ReleaseDC(NULL, dc);
    if (dpi < 72 || dpi > 480) dpi = 96;
    g_dpi_scale = dpi / 96.0;
}

/* 逻辑基准尺寸 * 用户缩放 * 系统 DPI -> 物理像素 */
static int scaled_px(int base)
{
    double v = base * (g_cfg ? g_cfg->scale : 100) / 100.0 * g_dpi_scale;
    int r = (int)(v + 0.5);
    return r < 16 ? 16 : r;
}

void overlay_use_log(const wchar_t* path)
{
    if (path && path[0]) {
        wcsncpy(g_forced_log, path, MAX_PATH - 1);
        g_forced_log[MAX_PATH - 1] = 0;
    } else {
        g_forced_log[0] = 0;
    }
}

/* ---------------- 内存 DC ---------------- */

static void memdc_destroy(void)
{
    if (g_memdc) { DeleteDC(g_memdc); g_memdc = NULL; }
    if (g_membmp) { DeleteObject(g_membmp); g_membmp = NULL; }
}

static void memdc_rebuild(void)
{
    memdc_destroy();
    HDC scr = GetDC(NULL);
    g_memdc = CreateCompatibleDC(scr);
    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = g_w;
    bi.bmiHeader.biHeight = -g_h;          /* 自上而下 */
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = NULL;
    g_membmp = CreateDIBSection(scr, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    ReleaseDC(NULL, scr);
    if (g_membmp) SelectObject(g_memdc, g_membmp);
}

/* 把逻辑坐标映射设为 460x620 -> 窗口像素 */
static void memdc_begin_logical(void)
{
    SetMapMode(g_memdc, MM_ANISOTROPIC);
    SetWindowExtEx(g_memdc, HUD_BASE_W, HUD_BASE_H, NULL);
    SetViewportExtEx(g_memdc, g_w, g_h, NULL);
    SetViewportOrgEx(g_memdc, 0, 0, NULL);
}

static void memdc_end_logical(void)
{
    SetMapMode(g_memdc, MM_TEXT);
}

/* ---------------- 绘制 ---------------- */

static void layout_update(void)
{
    hud_layout(HUD_BASE_W, HUD_BASE_H, g_cfg->show_event_log, &g_layout);
}

static void paint(void)
{
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(g_hwnd, &ps);
    if (!dc) return;
    if (!g_memdc) { EndPaint(g_hwnd, &ps); return; }

    StatsView view;
    stats_view(&g_stats, g_stats.last_t, (double)g_cfg->stat_window, &view);

    memdc_begin_logical();
    hud_paint(g_memdc, &g_layout, g_cfg, &view, &g_evlog, g_status, g_logname, g_hover, g_log_scroll);
    memdc_end_logical();

    BitBlt(dc, 0, 0, g_w, g_h, g_memdc, 0, 0, SRCCOPY);
    EndPaint(g_hwnd, &ps);
}

/* ---------------- 窗口属性 ---------------- */

static void apply_topmost(void)
{
    SetWindowPos(g_hwnd, g_cfg->always_on_top ? HWND_TOPMOST : HWND_NOTOPMOST,
                 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

static void apply_alpha(void)
{
    SetLayeredWindowAttributes(g_hwnd, 0, (BYTE)g_cfg->alpha, LWA_ALPHA);
}

/* 鼠标穿透：分层窗口加上 WS_EX_TRANSPARENT 后，命中测试会直接落到下面的窗口，
 * 本窗口再也收不到鼠标消息（因此必须靠 Ctrl+Alt+T 关回来）。
 * 同时用 WM_NCHITTEST 返回 HTTRANSPARENT 兜底，两条路都堵死。 */
static void apply_click_through(void)
{
    LONG_PTR ex = GetWindowLongPtrW(g_hwnd, GWL_EXSTYLE);
    LONG_PTR want = g_cfg->click_through ? (ex | WS_EX_TRANSPARENT)
                                         : (ex & ~(LONG_PTR)WS_EX_TRANSPARENT);
    if (want != ex) {
        SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, want);
        SetWindowPos(g_hwnd, NULL, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }
    if (g_cfg->click_through) {
        /* 光标不在窗口上时悬停状态要清掉，否则按钮会一直亮着 */
        g_hover = HUD_BTN_NONE;
    }
}

static void apply_scale(void)
{
    g_w = scaled_px(HUD_BASE_W);
    g_h = scaled_px(HUD_BASE_H);
    SetWindowPos(g_hwnd, NULL, 0, 0, g_w, g_h,
                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    memdc_rebuild();
    InvalidateRect(g_hwnd, NULL, FALSE);
}

/* ---------------- 状态文本 ---------------- */

static void set_logname(void)
{
    const wchar_t* p = vlog_path(g_vlog);
    g_logname[0] = 0;
    if (g_demo) return;                     /* 演示模式的状态栏已经写明 */
    if (!p || !p[0]) return;
    const wchar_t* base = wcsrchr(p, L'\\');
    base = base ? base + 1 : p;
    char utf8[64];
    if (WideCharToMultiByte(CP_UTF8, 0, base, -1, utf8, sizeof(utf8), NULL, NULL) > 0)
        snprintf_(g_logname, sizeof(g_logname), "%s", utf8);
}

static void update_status(void)
{
    set_logname();

    if (g_demo) {
        snprintf_(g_status, sizeof(g_status), "%s", TXT_DEMO);
        return;
    }
    if (vlog_status(g_vlog) != 1) {
        snprintf_(g_status, sizeof(g_status), "%s",
                  vlog_forced_only(g_vlog) ? TXT_LOG_FILE_MISSING : TXT_LOG_MISSING);
        return;
    }
    if (!g_stats.in_world) {
        snprintf_(g_status, sizeof(g_status), "%s", TXT_WAIT_JOIN);
        return;
    }
    if (g_stats.in_fight) {
        const char* b = g_stats.cur_fight.disp[0] ? g_stats.cur_fight.disp : "Boss";
        snprintf_(g_status, sizeof(g_status), "%s · %s", TXT_RUNNING, b);
        return;
    }
    if (g_stats.intermission) {
        snprintf_(g_status, sizeof(g_status), "%s · %s %d", TXT_RUNNING, TXT_INTERMISSION,
                  g_stats.stage_no);
        return;
    }
    snprintf_(g_status, sizeof(g_status), "%s", TXT_IDLE_WORLD);
}

/* ---------------- 事件日志 ---------------- */

/* ---------------- 日志轮询 ---------------- */

static void consume_line(const char* line)
{
    Event e;
    if (!parse_line(line, &e)) return;
    if (!stats_on_event(&g_stats, &e)) return;   /* 噪声（如非 Boss 的 ownership 行）*/
    evtext_push(&g_evlog, &g_stats, &e);
    update_status();
}

static void poll_logs(void)
{
    if (vlog_take_rotated(g_vlog)) {
        Event e;
        memset(&e, 0, sizeof(e));
        e.type = EV_ROOM_LEFT;
        e.t = g_stats.last_t > 0 ? g_stats.last_t + 0.001 : 0;
        stats_on_event(&g_stats, &e);
        evlog_push(&g_evlog, e.t, EVK_BOSS, "%s", TXT_EV_WORLD_OUT);
        update_status();
    }

    char line[2048];
    DWORD start = GetTickCount();
    int n = 0;
    int r = 0;
    while ((r = vlog_poll(g_vlog, line, (int)sizeof(line))) == 1) {
        consume_line(line);
        if (++n >= 50000) break;
        if ((n & 0x7F) == 0 && GetTickCount() - start > 12) break;   /* 回放时也让界面喘息 */
    }
    if (r == -1) update_status();
}

/* ---------------- 交互 ---------------- */

static void on_button(int btn)
{
    switch (btn) {
    case HUD_BTN_TOPMOST:
        g_cfg->always_on_top = !g_cfg->always_on_top;
        apply_topmost();
        break;
    case HUD_BTN_BIGGER:
        if (g_cfg->scale < CFG_SCALE_MAX) { g_cfg->scale += CFG_SCALE_STEP; apply_scale(); }
        break;
    case HUD_BTN_SMALLER:
        if (g_cfg->scale > CFG_SCALE_MIN) { g_cfg->scale -= CFG_SCALE_STEP; apply_scale(); }
        break;
    case HUD_BTN_OPAQUE:
        if (g_cfg->alpha < CFG_ALPHA_MAX) {
            g_cfg->alpha += 15;
            if (g_cfg->alpha > CFG_ALPHA_MAX) g_cfg->alpha = CFG_ALPHA_MAX;
            apply_alpha();
        }
        break;
    case HUD_BTN_TRANSPARENT:
        if (g_cfg->alpha > CFG_ALPHA_MIN) {
            g_cfg->alpha -= 15;
            if (g_cfg->alpha < CFG_ALPHA_MIN) g_cfg->alpha = CFG_ALPHA_MIN;
            apply_alpha();
        }
        break;
    case HUD_BTN_PIERCE:
        g_cfg->click_through = !g_cfg->click_through;
        apply_click_through();
        break;
    case HUD_BTN_LOG:
        g_cfg->show_event_log = !g_cfg->show_event_log;
        g_log_scroll = 0;
        layout_update();
        break;
    case HUD_BTN_LOG_UP: {
        int vis = evlog_visible(&g_evlog, g_cfg->ev_filter);
        int maxs = vis > 1 ? vis - 1 : 0;
        if (g_log_scroll < maxs) g_log_scroll++;
        break;
    }
    case HUD_BTN_LOG_DOWN:
        if (g_log_scroll > 0) g_log_scroll--;
        break;
    case HUD_BTN_FILT_ALL:
    case HUD_BTN_FILT_DAMAGE:
    case HUD_BTN_FILT_TARGET:
    case HUD_BTN_FILT_BOSS:
        g_cfg->ev_filter = btn - HUD_BTN_FILT_ALL;
        g_log_scroll = 0;                  /* 换过滤器后回到最新一条 */
        break;
    case HUD_BTN_PREV_RUN:
        stats_view_run_step(&g_stats, -1);
        break;
    case HUD_BTN_NEXT_RUN:
        stats_view_run_step(&g_stats, 1);
        break;
    case HUD_BTN_PREV_FIGHT:
        stats_view_fight_step(&g_stats, -1);
        break;
    case HUD_BTN_NEXT_FIGHT:
        stats_view_fight_step(&g_stats, 1);
        break;
    case HUD_BTN_CLOSE:
        PostMessageW(g_hwnd, WM_CLOSE, 0, 0);
        break;
    default:
        break;
    }
    InvalidateRect(g_hwnd, NULL, FALSE);
}

static void to_logical(int x, int y, int* lx, int* ly)
{
    *lx = (int)((double)x * HUD_BASE_W / (g_w > 0 ? g_w : 1));
    *ly = (int)((double)y * HUD_BASE_H / (g_h > 0 ? g_h : 1));
}

static void track_leave(void)
{
    if (g_tracking) return;
    TRACKMOUSEEVENT tme;
    memset(&tme, 0, sizeof(tme));
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = g_hwnd;
    if (TrackMouseEvent(&tme)) g_tracking = true;
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE:
        SetTimer(hwnd, 1, TIMER_POLL, NULL);
        return 0;

    case WM_TIMER:
        poll_logs();
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;

    case WM_PAINT:
        paint();
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_DPICHANGED: {
        HDC dc = GetDC(NULL);
        int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : 96;
        if (dc) ReleaseDC(NULL, dc);
        if (dpi >= 72 && dpi <= 480) g_dpi_scale = dpi / 96.0;
        g_w = scaled_px(HUD_BASE_W);
        g_h = scaled_px(HUD_BASE_H);
        const RECT* pr = (const RECT*)lp;
        SetWindowPos(hwnd, NULL, pr->left, pr->top, g_w, g_h,
                     SWP_NOZORDER | SWP_NOACTIVATE);
        memdc_rebuild();
        return 0;
    }

    case WM_SIZE:
        if (wp != SIZE_MINIMIZED) {
            g_w = LOWORD(lp);
            g_h = HIWORD(lp);
            if (g_w < 1) g_w = 1;
            if (g_h < 1) g_h = 1;
            memdc_rebuild();
        }
        return 0;

    case WM_NCHITTEST:
        /* 双保险：即使 WS_EX_TRANSPARENT 没生效，也把命中测试让给下层窗口 */
        if (g_cfg && g_cfg->click_through) return HTTRANSPARENT;
        break;

    case WM_LBUTTONDOWN: {
        int lx, ly;
        to_logical(GET_X_LPARAM(lp), GET_Y_LPARAM(lp), &lx, &ly);
        int btn = hud_hit_test(lx, ly, &g_layout);
        if (btn == HUD_BTN_DRAG) {
            g_dragging = true;
            g_drag_pt.x = GET_X_LPARAM(lp);
            g_drag_pt.y = GET_Y_LPARAM(lp);
            SetCapture(hwnd);
        } else {
            on_button(btn);
        }
        return 0;
    }

    case WM_LBUTTONUP:
        if (g_dragging) {
            g_dragging = false;
            ReleaseCapture();
        }
        return 0;

    case WM_CAPTURECHANGED:
        g_dragging = false;
        return 0;

    case WM_MOUSEMOVE: {
        int x = GET_X_LPARAM(lp), y = GET_Y_LPARAM(lp);
        track_leave();
        if (g_dragging) {
            RECT r;
            GetWindowRect(hwnd, &r);
            SetWindowPos(hwnd, NULL, r.left + (x - g_drag_pt.x), r.top + (y - g_drag_pt.y),
                         0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            return 0;
        }
        int lx, ly;
        to_logical(x, y, &lx, &ly);
        int hov = hud_hit_test(lx, ly, &g_layout);
        if (hov != g_hover) {
            g_hover = hov;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    }

    case WM_MOUSELEAVE:
        g_tracking = false;
        if (g_hover != HUD_BTN_NONE) {
            g_hover = HUD_BTN_NONE;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;

    case WM_RBUTTONDOWN:
        g_cfg->ev_filter = (g_cfg->ev_filter + 1) % EVFILT_COUNT;
        g_log_scroll = 0;
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;

    case WM_MOUSEWHEEL: {
        int delta = GET_WHEEL_DELTA_WPARAM(wp);
        if (delta > 0) g_log_scroll++;
        else if (g_log_scroll > 0) g_log_scroll--;
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }

    case WM_KEYDOWN:
        if (wp == VK_ESCAPE) { PostMessageW(hwnd, WM_CLOSE, 0, 0); return 0; }
        break;

    case WM_HOTKEY:
        if (wp == HOTKEY_QUIT) PostMessageW(hwnd, WM_CLOSE, 0, 0);
        else if (wp == HOTKEY_PIERCE) {
            /* 穿透后窗口收不到鼠标消息，只能靠这个热键关回来 */
            g_cfg->click_through = !g_cfg->click_through;
            apply_click_through();
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;

    case WM_DESTROY:
        /* 窗口此刻仍然有效，先把位置记下来供退出时保存配置 */
        GetWindowRect(hwnd, &g_last_rect);
        KillTimer(hwnd, 1);
        UnregisterHotKey(hwnd, HOTKEY_QUIT);
        UnregisterHotKey(hwnd, HOTKEY_PIERCE);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

/* ---------------- 入口 ---------------- */

void overlay_run(Config* cfg, bool demo, bool from_start)
{
    g_cfg = cfg;
    g_demo = demo;
    init_dpi();
    stats_init(&g_stats);
    evlog_init(&g_evlog);
    g_vlog = vlog_open(g_forced_log[0] ? g_forced_log : NULL, demo, from_start);
    update_status();

    WNDCLASSW wc;
    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = L"EclipticaHudC";
    wc.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
    wc.hbrBackground = NULL;
    if (!RegisterClassW(&wc)) {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return;
    }

    g_w = scaled_px(HUD_BASE_W);
    g_h = scaled_px(HUD_BASE_H);
    if (g_w < 1) g_w = HUD_BASE_W;
    if (g_h < 1) g_h = HUD_BASE_H;

    int sx = cfg->win_x, sy = cfg->win_y;
    if (sx < -30000 || sy < -30000 || sx < 0 || sy < 0 ||
        sx > GetSystemMetrics(SM_CXSCREEN) - 40 ||
        sy > GetSystemMetrics(SM_CYSCREEN) - 40) {
        sx = (GetSystemMetrics(SM_CXSCREEN) - g_w) / 2;
        sy = (GetSystemMetrics(SM_CYSCREEN) - g_h) / 4;
        if (sy < 0) sy = 0;
    }

    g_hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        L"EclipticaHudC", L"Ecliptica HUD",
        WS_POPUP,
        sx, sy, g_w, g_h, NULL, NULL, wc.hInstance, NULL);
    if (!g_hwnd) return;

    layout_update();
    memdc_rebuild();
    if (!cfg->always_on_top) {
        SetWindowPos(g_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    apply_alpha();
    RegisterHotKey(g_hwnd, HOTKEY_QUIT, HOTKEY_ID_MOD, 'Q');
    RegisterHotKey(g_hwnd, HOTKEY_PIERCE, HOTKEY_ID_MOD, 'T');
    apply_click_through();          /* 恢复上次退出时的穿透状态 */

    ShowWindow(g_hwnd, SW_SHOWNOACTIVATE);
    UpdateWindow(g_hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    RECT r;
    if (g_last_rect.right > g_last_rect.left) r = g_last_rect;
    else if (!GetWindowRect(g_hwnd, &r)) { r.left = 0; r.top = 0; }
    g_cfg->win_x = r.left;
    g_cfg->win_y = r.top;

    memdc_destroy();
    hud_free_fonts();
    vlog_close(g_vlog);
    g_vlog = NULL;
}
