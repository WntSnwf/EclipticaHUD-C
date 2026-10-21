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
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define TIMER_POLL    100
#define HOTKEY_QUIT   1
#define HOTKEY_PIERCE 2

/* 托盘图标：右键菜单的消息、菜单项编号 */
#define WM_TRAY_NOTIFY  (WM_APP + 1)
#define IDM_TRAY_TOP    1
#define IDM_TRAY_PIERCE 2
#define IDM_TRAY_QUIT   3
#define TRAY_UID        1

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

/* 实际注册成功的快捷键（空串 = 注册失败/被占用）。
 * 托盘菜单靠它告诉用户"现在按哪个键能退出"，而不是永远写死 Ctrl+Alt+Q。*/
static wchar_t  g_quit_hotkey[48];
static wchar_t  g_pierce_hotkey[48];

/* 托盘相关（定义在下面，apply_click_through 要用到）*/
static void tray_update_tip(void);
static void tray_add(void);
static void tray_remove(void);

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
    tray_update_tip();
}

/* ---------------- 托盘图标 ----------------
 *
 * 为什么必须有：
 *   窗口是 WS_EX_TOOLWINDOW + WS_EX_NOACTIVATE，所以任务栏里没有它；
 *   一旦开了鼠标穿透，窗口本身收不到任何鼠标消息 —— 这时如果
 *   Ctrl+Alt+T / Ctrl+Alt+Q 又被别的程序占用了，用户**没有任何办法退出**，
 *   只能去任务管理器强杀。托盘图标属于桌面外壳，不受穿透影响，
 *   所以它是最后一道可点的逃生口。
 */

static HICON    g_tray_icon;
static NOTIFYICONDATAW g_nid;
static bool     g_tray_added;
static int      g_tray_tries;   /* 外壳没就绪时的重试计数 */

/* 运行时画一个小图标（深色底 + 青色圆点，和面板标题栏一致），
 * 这样不用额外的 .rc/.ico 资源，MinGW 与 MSVC 都能直接编。
 *
 * ⚠ 这里有个坑：**必须用 DIB section，不能用 CreateCompatibleBitmap**。
 * GDI 的绘制函数（FillRect / Ellipse …）只写 RGB，**从不写 alpha**；
 * CreateCompatibleBitmap 在 32bpp 屏上得到的位图 alpha 全是 0，
 * CreateIconIndirect 之后图标就是"全透明"的 —— 托盘项其实加进去了，
 * 但画出来什么都看不见（实测 alpha 非 0 的像素 0/256）。
 * 所以：自己建 32bpp DIB，画完把每个像素的 alpha 置 255。*/
static HICON make_tray_icon(void)
{
    int S = GetSystemMetrics(SM_CXSMICON);
    if (S < 16) S = 16;

    HDC screen = GetDC(NULL);
    if (!screen) return NULL;
    HDC dc = CreateCompatibleDC(screen);
    if (!dc) { ReleaseDC(NULL, screen); return NULL; }

    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = S;
    bi.bmiHeader.biHeight = -S;              /* 负高度 = 自上而下，和 GDI 坐标一致 */
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP color = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    HBITMAP maskb = CreateBitmap(S, S, 1, 1, NULL);
    if (!color || !bits || !maskb) {
        if (color) DeleteObject(color);
        if (maskb) DeleteObject(maskb);
        DeleteDC(dc);
        ReleaseDC(NULL, screen);
        return NULL;
    }

    HGDIOBJ oldbmp = SelectObject(dc, color);
    RECT r;
    r.left = 0; r.top = 0; r.right = S; r.bottom = S;
    HBRUSH bg = CreateSolidBrush(RGB(20, 25, 35));
    FillRect(dc, &r, bg);
    DeleteObject(bg);

    int inset = S / 16;
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(56, 68, 92));
    HGDIOBJ op = SelectObject(dc, pen);
    HGDIOBJ ob = SelectObject(dc, GetStockObject(NULL_BRUSH));
    Rectangle(dc, inset, inset, S - inset, S - inset);

    int pad = S / 4;
    HBRUSH dot = CreateSolidBrush(RGB(118, 188, 255));
    SelectObject(dc, dot);
    SelectObject(dc, GetStockObject(NULL_PEN));
    Ellipse(dc, pad, pad, S - pad, S - pad);

    SelectObject(dc, ob);
    SelectObject(dc, op);
    DeleteObject(pen);
    DeleteObject(dot);
    SelectObject(dc, oldbmp);

    /* 关键一步：GDI 没写 alpha，这里补成完全不透明，否则图标是透明的 */
    {
        unsigned char* px = (unsigned char*)bits;
        for (int i = 0; i < S * S; i++) px[i * 4 + 3] = 255;
    }

    /* 全 0 的掩码 = 整块不透明（用颜色位图的形状） */
    HDC mdc = CreateCompatibleDC(screen);
    if (mdc) {
        HGDIOBJ om = SelectObject(mdc, maskb);
        RECT mr;
        mr.left = 0; mr.top = 0; mr.right = S; mr.bottom = S;
        HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(mdc, &mr, black);
        DeleteObject(black);
        SelectObject(mdc, om);
        DeleteDC(mdc);
    }

    ICONINFO ii;
    memset(&ii, 0, sizeof(ii));
    ii.fIcon = TRUE;
    ii.hbmMask = maskb;
    ii.hbmColor = color;
    HICON ic = CreateIconIndirect(&ii);

    DeleteObject(color);
    DeleteObject(maskb);
    DeleteDC(dc);
    ReleaseDC(NULL, screen);
    return ic;
}

static void tray_update_tip(void)
{
    if (!g_tray_added) return;
    const char* tip = (g_cfg && g_cfg->click_through) ? TXT_TRAY_TIP_PIERCE : TXT_TRAY_TIP;
    MultiByteToWideChar(CP_UTF8, 0, tip, -1, g_nid.szTip,
                        (int)(sizeof(g_nid.szTip) / sizeof(g_nid.szTip[0])));
    g_nid.uFlags = NIF_TIP;
    Shell_NotifyIconW(NIM_MODIFY, &g_nid);
    g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
}

static void tray_add(void)
{
    memset(&g_nid, 0, sizeof(g_nid));
    g_nid.cbSize = sizeof(g_nid);
    g_nid.hWnd = g_hwnd;
    g_nid.uID = TRAY_UID;
    g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_nid.uCallbackMessage = WM_TRAY_NOTIFY;
    if (!g_tray_icon) g_tray_icon = make_tray_icon();
    g_nid.hIcon = g_tray_icon ? g_tray_icon : LoadIconW(NULL, IDI_APPLICATION);
    MultiByteToWideChar(CP_UTF8, 0, TXT_TRAY_TIP, -1, g_nid.szTip,
                        (int)(sizeof(g_nid.szTip) / sizeof(g_nid.szTip[0])));
    g_tray_added = Shell_NotifyIconW(NIM_ADD, &g_nid) != FALSE;
    if (g_tray_added) tray_update_tip();
}

static void tray_remove(void)
{
    if (g_tray_added) {
        Shell_NotifyIconW(NIM_DELETE, &g_nid);
        g_tray_added = false;
    }
    if (g_tray_icon) {
        DestroyIcon(g_tray_icon);
        g_tray_icon = NULL;
    }
}

/* 菜单项文字：本地化之后拼上实际可用的快捷键；注册失败就直说 */
static void tray_item_label(wchar_t* out, int cap, const char* label,
                            const wchar_t* hotkey)
{
    wchar_t wl[128];
    MultiByteToWideChar(CP_UTF8, 0, label, -1, wl, 128);
    if (hotkey && hotkey[0]) snwprintf_(out, (size_t)cap, L"%s\t%s", wl, hotkey);
    else {
        wchar_t wh[128];
        MultiByteToWideChar(CP_UTF8, 0, TXT_TRAY_NO_HOTKEY, -1, wh, 128);
        snwprintf_(out, (size_t)cap, L"%s   %s", wl, wh);
    }
}

/* 注册全局快捷键，失败时自动退到备选组合。
 *
 * 为什么要在意失败：RegisterHotKey 会被别的程序抢走（输入法、录屏、Steam 之类）。
 * 一旦 Ctrl+Alt+T 没注册上，用户开了穿透就再也点不到面板；
 * 如果 Ctrl+Alt+Q 也没注册上，那就只能强杀进程了。所以：
 *   1. 先试文档里写的组合；
 *   2. 不行就换一个不那么容易撞的组合；
 *   3. 都失败就把 g_*_hotkey 留空 —— 托盘菜单会显示"快捷键被占用"，
 *      并保证从托盘还能把穿透关掉、把程序退掉。*/
static void register_hotkeys(void)
{
    static const struct { UINT mod; UINT vk; const wchar_t* name; } QUIT_KEYS[] = {
        { HOTKEY_ID_MOD, 'Q',                        L"Ctrl+Alt+Q" },
        { MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 'Q', L"Ctrl+Shift+Q" },
        { MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F10, L"Ctrl+Alt+F10" },
    };
    static const struct { UINT mod; UINT vk; const wchar_t* name; } PIERCE_KEYS[] = {
        { HOTKEY_ID_MOD, 'T',                        L"Ctrl+Alt+T" },
        { MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 'T', L"Ctrl+Shift+T" },
        { MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F9, L"Ctrl+Alt+F9" },
    };

    g_quit_hotkey[0] = 0;
    g_pierce_hotkey[0] = 0;

    for (size_t i = 0; i < sizeof(QUIT_KEYS) / sizeof(QUIT_KEYS[0]); i++) {
        if (RegisterHotKey(g_hwnd, HOTKEY_QUIT, QUIT_KEYS[i].mod, QUIT_KEYS[i].vk)) {
            snwprintf_(g_quit_hotkey, 48, L"%s", QUIT_KEYS[i].name);
            break;
        }
    }
    for (size_t i = 0; i < sizeof(PIERCE_KEYS) / sizeof(PIERCE_KEYS[0]); i++) {
        if (RegisterHotKey(g_hwnd, HOTKEY_PIERCE, PIERCE_KEYS[i].mod, PIERCE_KEYS[i].vk)) {
            snwprintf_(g_pierce_hotkey, 48, L"%s", PIERCE_KEYS[i].name);
            break;
        }
    }
}

static void tray_command(HWND hwnd, UINT id)
{
    switch (id) {
    case IDM_TRAY_TOP:
        g_cfg->always_on_top = !g_cfg->always_on_top;
        SetWindowPos(hwnd, g_cfg->always_on_top ? HWND_TOPMOST : HWND_NOTOPMOST,
                     0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case IDM_TRAY_PIERCE:
        g_cfg->click_through = !g_cfg->click_through;
        apply_click_through();
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case IDM_TRAY_QUIT:
        PostMessageW(hwnd, WM_CLOSE, 0, 0);
        break;
    default:
        break;
    }
}

static void tray_show_menu(void)
{
    HMENU m = CreatePopupMenu();
    if (!m) return;

    wchar_t lbl[256];

    tray_item_label(lbl, 256, TXT_TRAY_TOP, NULL);
    AppendMenuW(m, MF_STRING | (g_cfg->always_on_top ? MF_CHECKED : 0), IDM_TRAY_TOP, lbl);

    tray_item_label(lbl, 256, TXT_TRAY_PIERCE, g_pierce_hotkey[0] ? g_pierce_hotkey : NULL);
    AppendMenuW(m, MF_STRING | (g_cfg->click_through ? MF_CHECKED : 0), IDM_TRAY_PIERCE, lbl);

    AppendMenuW(m, MF_SEPARATOR, 0, NULL);

    tray_item_label(lbl, 256, TXT_TRAY_QUIT, g_quit_hotkey[0] ? g_quit_hotkey : NULL);
    AppendMenuW(m, MF_STRING, IDM_TRAY_QUIT, lbl);

    POINT p;
    GetCursorPos(&p);

    /* ⚠ 窗口是 WS_EX_NOACTIVATE，直接 SetForegroundWindow 会失败，菜单就"没有主人"：
     * 一松手/一动鼠标就被系统关掉，看起来像菜单闪一下就没了、根本点不到。
     * 解决：临时去掉 NOACTIVATE 让菜单能拿前台，菜单结束后立刻恢复
     * （所以面板平时仍然不抢 VRChat 的焦点）。
     * 选中项用 TPM_RETURNCMD 取返回值，不依赖 WM_COMMAND 投递 —— 
     * 非激活窗口收菜单结果并不可靠。*/
    HWND prev = GetForegroundWindow();
    LONG_PTR ex = GetWindowLongPtrW(g_hwnd, GWL_EXSTYLE);
    SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, ex & ~(LONG_PTR)WS_EX_NOACTIVATE);
    SetForegroundWindow(g_hwnd);

    UINT cmd = (UINT)TrackPopupMenu(m, TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_BOTTOMALIGN,
                                    p.x, p.y, 0, g_hwnd, NULL);

    SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, ex);     /* 立刻恢复：不抢焦点 */
    DestroyMenu(m);
    if (prev && prev != g_hwnd && IsWindow(prev)) SetForegroundWindow(prev);
    PostMessageW(g_hwnd, WM_NULL, 0, 0);

    if (cmd) tray_command(g_hwnd, cmd);
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
        /* 开机自启时外壳可能还没准备好，Shell_NotifyIcon 会失败 ——
         * 每隔约 2 秒重试一次，最多 15 次（共约 30 秒）。*/
        if (!g_tray_added && g_tray_tries < 15) {
            static int tick = 0;
            if (++tick % 20 == 0) {
                g_tray_tries++;
                tray_add();
            }
        }
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

    case WM_TRAY_NOTIFY:
        switch (LOWORD(lp)) {
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
            tray_show_menu();
            return 0;
        case WM_LBUTTONDBLCLK:
            /* 双击：把穿透关掉（穿透状态下窗口点不到，这里是最直觉的补救）*/
            if (g_cfg->click_through) {
                g_cfg->click_through = false;
                apply_click_through();
                InvalidateRect(hwnd, NULL, FALSE);
            } else {
                SetForegroundWindow(hwnd);
            }
            return 0;
        }
        return 0;

    case WM_COMMAND:
        /* 正常情况下菜单走 TPM_RETURNCMD，不会到这里；
         * 保留是为了兜住其它来源（例如以后给面板加右键菜单）。*/
        tray_command(hwnd, (UINT)LOWORD(wp));
        return 0;

    case WM_DESTROY:
        /* 窗口此刻仍然有效，先把位置记下来供退出时保存配置 */
        GetWindowRect(hwnd, &g_last_rect);
        KillTimer(hwnd, 1);
        tray_remove();
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
    register_hotkeys();
    tray_add();                     /* 托盘图标：穿透开着时的唯一逃生口 */
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
