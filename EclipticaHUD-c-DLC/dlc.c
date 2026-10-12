/* dlc.c - Ecliptica HUD DLC：Boss 弱点 / 抗性面板
 *
 * 独立小程序，不修改本体 ecliptica-hud-c：它只做一件事 —— 跟随 VRChat 日志
 * 认出"当前正在打哪个 Boss"，然后把 Weakness&Resistance.txt 里对应的
 * 弱点 / 抗性显示成一块小面板。
 *
 * 用法：
 *   hr-dlc.exe                     自动定位日志并跟随
 *   hr-dlc.exe --log 文件          只看这一个日志文件
 *   hr-dlc.exe --boss FlyLord      不读日志，固定显示某只 Boss（调试用）
 *   hr-dlc.exe --demo              用内置的轮播演示（无需日志）
 *   hr-dlc.exe --help
 *
 * 操作：拖动面板移动；点右上 ✕ 关闭；Ctrl+Alt+W 全局退出。
 */
/* 需要 Win7 以上的 API（SetProcessDPIAware 等）*/
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#include "dlcui.h"
#include "logtail.h"
#include "res.h"
#include "uitext.h"
#include "compat.h"
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMER_POLL  200
#define HOTKEY_QUIT 1
#define HOTKEY_ID_MOD (MOD_CONTROL | MOD_ALT | MOD_NOREPEAT)

#ifndef MOD_NOREPEAT
#define MOD_NOREPEAT 0x4000
#endif
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif

/* ---------------- 状态 ---------------- */
static HWND     g_hwnd;
static HDC      g_memdc;
static HBITMAP  g_bmp;
static void*    g_bits;
static int      g_w = DLC_W, g_h = DLC_H;   /* 窗口像素尺寸 */
static double   g_dpi = 1.0;
static int      g_alpha = 230;
static int      g_hover_close = 0;
static int      g_dragging = 0;
static POINT    g_drag_pt;
static RECT     g_last_rect;
static double   g_flash_until = 0;

static ResTable g_res;
static bool     g_res_ok = false;
static LogTail  g_tail;
static DlcLayout g_layout;

/* 数据文件与配置文件的路径（都在 exe 同目录）*/
static wchar_t g_res_path[MAX_PATH];
static wchar_t g_ini_path[MAX_PATH];

/* --boss / --demo 时的固定值 */
static char     g_forced_boss[64];
static bool     g_demo = false;

/* ---------------- 路径 ---------------- */

static void exe_dir(wchar_t* out, int cap)
{
    wchar_t tmp[MAX_PATH];
    DWORD n = GetModuleFileNameW(NULL, tmp, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) { snwprintf_(out, (size_t)cap, L"."); return; }
    wchar_t* slash = wcsrchr(tmp, L'\\');
    if (slash) *slash = 0;
    snwprintf_(out, (size_t)cap, L"%s", tmp);
}

static void build_paths(void)
{
    wchar_t dir[MAX_PATH];
    exe_dir(dir, MAX_PATH);
    snwprintf_(g_res_path, MAX_PATH, L"%s\\Weakness&Resistance.txt", dir);
    snwprintf_(g_ini_path, MAX_PATH, L"%s\\hr-dlc.ini", dir);
}

/* ---------------- 配置（窗口位置 / 透明度）---------------- */

static void cfg_load_pos(int* x, int* y)
{
    *x = -1; *y = -1;
    FILE* f = _wfopen(g_ini_path, L"rb");
    if (!f) return;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (!strncmp(line, "win_x=", 6)) *x = atoi(line + 6);
        else if (!strncmp(line, "win_y=", 6)) *y = atoi(line + 6);
        else if (!strncmp(line, "alpha=", 6)) g_alpha = atoi(line + 6);
    }
    fclose(f);
    if (g_alpha < 60) g_alpha = 60;
    if (g_alpha > 255) g_alpha = 255;
}

/* ---------------- DPI / 双缓冲 ---------------- */

static void init_dpi(void)
{
    typedef BOOL (WINAPI *SetCtxFn)(HANDLE);
    HMODULE u = LoadLibraryW(L"user32.dll");
    if (u) {
        /* -4 = PER_MONITOR_AWARE_V2，-3 = PER_MONITOR_AWARE */
        SetCtxFn f = (SetCtxFn)(void*)GetProcAddress(u, "SetProcessDpiAwarenessContext");
        if (f && !f((HANDLE)(INT_PTR)-4)) f((HANDLE)(INT_PTR)-3);
        else if (!f) SetProcessDPIAware();
    }
    HDC dc = GetDC(NULL);
    int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : 96;
    if (dc) ReleaseDC(NULL, dc);
    if (dpi >= 72 && dpi <= 480) g_dpi = dpi / 96.0;
    g_w = (int)(DLC_W * g_dpi + 0.5);
    g_h = (int)(DLC_H * g_dpi + 0.5);
    if (g_w < 80) g_w = 80;
    if (g_h < 60) g_h = 60;
}

static void memdc_rebuild(void)
{
    if (g_memdc) { DeleteDC(g_memdc); g_memdc = NULL; }
    if (g_bmp) { DeleteObject(g_bmp); g_bmp = NULL; }
    HDC screen = GetDC(NULL);
    g_memdc = CreateCompatibleDC(screen);
    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = g_w;
    bi.bmiHeader.biHeight = -g_h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    g_bmp = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &g_bits, NULL, 0);
    ReleaseDC(NULL, screen);
    if (g_bmp) SelectObject(g_memdc, g_bmp);
}

static void logical_begin(void)
{
    SetMapMode(g_memdc, MM_ANISOTROPIC);
    SetWindowExtEx(g_memdc, DLC_W, DLC_H, NULL);
    SetViewportExtEx(g_memdc, g_w, g_h, NULL);
}

static void logical_end(void)
{
    SetMapMode(g_memdc, MM_TEXT);
}

/* ---------------- 视图合成 ---------------- */

static const BossRes* g_cur_res = NULL;
static char g_cur_display[96];
static int  g_cur_phase = 1;
static bool g_cur_in_fight = false;

static void refresh_view(void)
{
    const char* internal = NULL;
    int phase = 1;
    bool in_fight = false;

    if (g_forced_boss[0]) {
        internal = g_forced_boss;
        phase = res_boss_phase(g_forced_boss);
        in_fight = true;
    } else if (g_demo) {
        static const char* SEQ[] = { "FlyLord", "YukiPhase2", "NaN", "JimBringer",
                                     "ManalyteAncient", "DarkMouth", "Corus" };
        static int idx = 0;
        static double next = 0;
        double t = (double)GetTickCount64() / 1000.0;
        if (t >= next) { next = t + 4.0; idx = (idx + 1) % (int)(sizeof(SEQ)/sizeof(SEQ[0])); }
        internal = SEQ[idx];
        phase = res_boss_phase(internal);
        in_fight = true;
    } else if (g_tail.in_fight && g_tail.boss[0]) {
        internal = g_tail.boss;
        phase = g_tail.phase;
        in_fight = true;
    }

    const char* prev = g_cur_display[0] ? g_cur_display : NULL;
    char prev_disp[96];
    snprintf(prev_disp, sizeof(prev_disp), "%s", g_cur_display);

    if (in_fight && internal) {
        const char* disp = res_boss_display(internal);
        snprintf(g_cur_display, sizeof(g_cur_display), "%s", disp);
        g_cur_phase = phase;
        g_cur_in_fight = true;
        g_cur_res = res_find(&g_res, internal, phase);
    } else {
        g_cur_display[0] = 0;
        g_cur_phase = 1;
        g_cur_in_fight = false;
        g_cur_res = NULL;
    }
    if (strcmp(prev_disp, g_cur_display) != 0)
        g_flash_until = (double)GetTickCount64() / 1000.0 + 0.8;
    (void)prev;
}

static void build_view(DlcView* v, char* status, int scap, char* logname, int lcap)
{
    v->boss_display = g_cur_display;
    v->phase = g_cur_phase;
    v->in_fight = g_cur_in_fight;
    v->res = g_cur_res;
    logname[0] = 0;

    /* 统一用 "%s"：文案里万一带 % 也不会被当成格式符 */
    if (g_forced_boss[0]) {
        snprintf(status, (size_t)scap, "%s", TXT_ST_FORCED);
    } else if (g_demo) {
        snprintf(status, (size_t)scap, "%s", TXT_ST_DEMO);
    } else if (!g_res_ok) {
        snprintf(status, (size_t)scap, "%s", TXT_ST_NO_TABLE);
    } else if (!logtail_ready(&g_tail)) {
        snprintf(status, (size_t)scap, "%s", TXT_ST_NO_LOG);
    } else {
        snprintf(status, (size_t)scap, "%s",
                 g_cur_in_fight ? TXT_ST_LOCKED : TXT_ST_WAITING);
        logtail_name(&g_tail, logname, lcap);
        /* 只显示时间戳部分更省地方：output_log_2026-10-12_19-00-00.txt
         *                                        -> 2026-10-12_19-00-00 */
        if (!strncmp(logname, "output_log_", 11))
            memmove(logname, logname + 11, strlen(logname + 11) + 1);
        size_t ln = strlen(logname);
        if (ln > 4 && !strcmp(logname + ln - 4, ".txt")) logname[ln - 4] = 0;
    }
    v->status = status;
    v->logname = logname;
}

/* ---------------- 绘制 ---------------- */

static void paint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);
    if (!g_memdc) { EndPaint(hwnd, &ps); return; }

    char status[192], logname[96];
    DlcView v;
    build_view(&v, status, sizeof(status), logname, sizeof(logname));

    logical_begin();
    double now = (double)GetTickCount64() / 1000.0;
    dlcui_paint(g_memdc, &g_layout, &v, g_hover_close, now < g_flash_until ? 1.0 : 0.0);
    logical_end();

    BitBlt(dc, 0, 0, g_w, g_h, g_memdc, 0, 0, SRCCOPY);
    EndPaint(hwnd, &ps);
}

/* ---------------- 窗口过程 ---------------- */

static void to_logical(int dx, int dy, int* lx, int* ly)
{
    *lx = (int)((double)dx * DLC_W / (g_w ? g_w : 1));
    *ly = (int)((double)dy * DLC_H / (g_h ? g_h : 1));
}

static void cfg_save(int x, int y)
{
    FILE* f = _wfopen(g_ini_path, L"wb");
    if (!f) return;
    fprintf(f, "# Ecliptica HUD DLC (weakness/resistance panel)\n");
    fprintf(f, "win_x=%d\n", x);
    fprintf(f, "win_y=%d\n", y);
    fprintf(f, "alpha=%d\n", g_alpha);
    fclose(f);
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE:
        SetTimer(hwnd, 1, TIMER_POLL, NULL);
        return 0;

    case WM_TIMER: {
        bool changed = false;
        if (!g_forced_boss[0] && !g_demo) changed = logtail_poll(&g_tail);
        if (g_demo) changed = true;                 /* 演示模式每次刷新都可能换 Boss */
        refresh_view();
        if (changed) InvalidateRect(hwnd, NULL, FALSE);
        else {
            /* 状态栏里的日志名/提示也可能变，低频重绘即可 */
            static int tick = 0;
            if ((++tick % 10) == 0) InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    }

    case WM_PAINT:
        paint(hwnd);
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_MOUSEMOVE: {
        int lx, ly;
        to_logical(GET_X_LPARAM(lp), GET_Y_LPARAM(lp), &lx, &ly);
        int hov = !strcmp(dlcui_hit(&g_layout, lx, ly), "close");
        if (hov != g_hover_close) { g_hover_close = hov; InvalidateRect(hwnd, NULL, FALSE); }
        if (g_dragging) {
            POINT p;
            GetCursorPos(&p);
            SetWindowPos(hwnd, NULL, p.x - g_drag_pt.x, p.y - g_drag_pt.y, 0, 0,
                         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
        return 0;
    }

    case WM_LBUTTONDOWN: {
        int lx, ly;
        to_logical(GET_X_LPARAM(lp), GET_Y_LPARAM(lp), &lx, &ly);
        if (!strcmp(dlcui_hit(&g_layout, lx, ly), "close")) {
            PostMessageW(hwnd, WM_CLOSE, 0, 0);
        } else {
            g_dragging = 1;
            g_drag_pt.x = GET_X_LPARAM(lp);
            g_drag_pt.y = GET_Y_LPARAM(lp);
            SetCapture(hwnd);
        }
        return 0;
    }

    case WM_LBUTTONUP:
        if (g_dragging) { g_dragging = 0; ReleaseCapture(); }
        return 0;

    case WM_NCHITTEST:
        /* 面板永远不吃点击以外的东西，保持不抢焦点 */
        break;

    case WM_DPICHANGED: {
        HDC dc = GetDC(NULL);
        int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : 96;
        if (dc) ReleaseDC(NULL, dc);
        if (dpi >= 72 && dpi <= 480) g_dpi = dpi / 96.0;
        g_w = (int)(DLC_W * g_dpi + 0.5);
        g_h = (int)(DLC_H * g_dpi + 0.5);
        const RECT* pr = (const RECT*)lp;
        SetWindowPos(hwnd, NULL, pr->left, pr->top, g_w, g_h, SWP_NOZORDER | SWP_NOACTIVATE);
        memdc_rebuild();
        return 0;
    }

    case WM_HOTKEY:
        if (wp == HOTKEY_QUIT) PostMessageW(hwnd, WM_CLOSE, 0, 0);
        return 0;

    case WM_DESTROY:
        GetWindowRect(hwnd, &g_last_rect);
        KillTimer(hwnd, 1);
        UnregisterHotKey(hwnd, HOTKEY_QUIT);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

/* ---------------- 入口 ---------------- */

static void show_help(void)
{
    MessageBoxA(NULL, TXT_HELP_BODY, TXT_HELP_TITLE, MB_OK | MB_ICONINFORMATION);
}

static bool arg_is(const wchar_t* a, const wchar_t* name)
{
    if (!a || a[0] != L'-') return false;
    a += (a[1] == L'-') ? 2 : 1;
    return _wcsicmp(a, name) == 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdline, int show)
{
    (void)hInst; (void)hPrev; (void)cmdline; (void)show;

    wchar_t logpath[MAX_PATH];
    logpath[0] = 0;
    bool bad = false;

    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv) {
        for (int i = 1; i < argc; i++) {
            if (arg_is(argv[i], L"log")) {
                if (i + 1 < argc) {
                    wcsncpy(logpath, argv[++i], MAX_PATH - 1);
                    logpath[MAX_PATH - 1] = 0;
                } else bad = true;
            } else if (arg_is(argv[i], L"boss")) {
                if (i + 1 < argc) {
                    WideCharToMultiByte(CP_UTF8, 0, argv[++i], -1, g_forced_boss,
                                        sizeof(g_forced_boss), NULL, NULL);
                    g_forced_boss[sizeof(g_forced_boss) - 1] = 0;
                } else bad = true;
            } else if (arg_is(argv[i], L"demo")) {
                g_demo = true;
            } else if (arg_is(argv[i], L"help") || arg_is(argv[i], L"h")) {
                LocalFree(argv);
                show_help();
                return 0;
            } else if (argv[i][0] == L'-') {
                bad = true;
            }
        }
        LocalFree(argv);
    }
    if (bad) { show_help(); return 0; }

    build_paths();
    {
        char path_a[MAX_PATH * 2];
        WideCharToMultiByte(CP_UTF8, 0, g_res_path, -1, path_a, sizeof(path_a), NULL, NULL);
        g_res_ok = res_load(&g_res, path_a);
    }
    {
        int x = -1, y = -1;
        cfg_load_pos(&x, &y);
        init_dpi();

        WNDCLASSW wc;
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc = wnd_proc;
        wc.hInstance = hInst;
        wc.lpszClassName = L"EclipticaHudDlcHR";
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        if (!RegisterClassW(&wc)) return 1;

        if (x < 0 || y < 0 || x > GetSystemMetrics(SM_CXSCREEN) - 40 ||
            y > GetSystemMetrics(SM_CYSCREEN) - 40) {
            x = GetSystemMetrics(SM_CXSCREEN) - g_w - 40;
            y = 120;
            if (x < 0) x = 0;
        }

        g_hwnd = CreateWindowExW(
            WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
            wc.lpszClassName, L"Ecliptica HR",
            WS_POPUP, x, y, g_w, g_h, NULL, NULL, hInst, NULL);
        if (!g_hwnd) return 1;

        dlcui_layout(&g_layout);
        memdc_rebuild();
        SetLayeredWindowAttributes(g_hwnd, 0, (BYTE)g_alpha, LWA_ALPHA);
        RegisterHotKey(g_hwnd, HOTKEY_QUIT, HOTKEY_ID_MOD, 'W');

        if (!g_forced_boss[0] && !g_demo) logtail_open(&g_tail, logpath[0] ? logpath : NULL);
        refresh_view();

        ShowWindow(g_hwnd, SW_SHOWNOACTIVATE);
        UpdateWindow(g_hwnd);

        MSG msg;
        while (GetMessageW(&msg, NULL, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        RECT r;
        if (g_last_rect.right > g_last_rect.left) r = g_last_rect;
        else if (!GetWindowRect(g_hwnd, &r)) { r.left = x; r.top = y; }
        cfg_save(r.left, r.top);

        logtail_close(&g_tail);
        dlcui_free_fonts();
        if (g_memdc) DeleteDC(g_memdc);
        if (g_bmp) DeleteObject(g_bmp);
    }
    return 0;
}
