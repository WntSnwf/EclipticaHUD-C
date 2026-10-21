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
#include "tablepath.h"
#include "uitext.h"
#include "compat.h"
#include <windowsx.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include <string.h>

#define TIMER_POLL  200
#define HOTKEY_QUIT 1
#define HOTKEY_ID_MOD (MOD_CONTROL | MOD_ALT | MOD_NOREPEAT)

/* 托盘图标：右键菜单的消息、菜单项编号。
 * 面板是 WS_EX_TOOLWINDOW，任务栏里没有它 —— 托盘图标是它唯一的落脚点。*/
#define WM_TRAY_NOTIFY  (WM_APP + 2)
#define IDM_TRAY_RELOAD 1
#define IDM_TRAY_QUIT   2
#define TRAY_UID        1

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

/* 抗性表 / 配置文件的实际路径 */
static wchar_t g_res_path[MAX_PATH];
static wchar_t g_res_hint[MAX_PATH];   /* 找不到表时，建议用户放到哪个目录 */
static bool    g_res_forced = false;   /* 是 --table 指定的（不做任何回退）*/
static wchar_t g_ini_path[MAX_PATH];

/* --boss / --demo 时的固定值 */
static char     g_forced_boss[64];
static bool     g_demo = false;
/* --table 指定的抗性表路径（空 = 按默认顺序查找）*/
static wchar_t  g_table_arg[MAX_PATH];

/* 托盘菜单操作后的临时状态提示（例如"抗性表已重读"），几秒后自动消失 */
static char     g_tray_msg[128];
static double   g_tray_msg_until;

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
    /* 解析 --boss / 演示序列时用；必须活到函数结束 */
    char arg_base[64];

    if (g_forced_boss[0]) {
        /* 走统一解析：YukiPhase2 / Jim C. Bringer(P2) 这些写法都能落到基础名+形态号，
         * 直接拿原字符串去查表会拼出 "YukiPhase2(P2)" 这种不存在的键。*/
        res_parse_boss_arg(g_forced_boss, arg_base, sizeof(arg_base), &phase);
        internal = arg_base;
        in_fight = true;
    } else if (g_demo) {
        static const char* SEQ[] = { "FlyLord", "YukiPhase2", "NaN", "JimBringer",
                                     "ManalyteAncient", "DarkMouth", "Corus" };
        static int idx = 0;
        static double next = 0;
        double t = (double)GetTickCount64() / 1000.0;
        if (t >= next) { next = t + 4.0; idx = (idx + 1) % (int)(sizeof(SEQ)/sizeof(SEQ[0])); }
        res_parse_boss_arg(SEQ[idx], arg_base, sizeof(arg_base), &phase);
        internal = arg_base;
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
    v->table_ok = g_res_ok;
    /* 找不到表时告诉用户该放哪儿；--table 指定过就直接显示那个路径 */
    {
        char hint[MAX_PATH * 2];
        const wchar_t* src = g_res_forced ? g_res_path : g_res_hint;
        WideCharToMultiByte(CP_UTF8, 0, src, -1, hint, sizeof(hint), NULL, NULL);
        hint[sizeof(hint) - 1] = 0;
        v->table_dir = hint;
    }
    logname[0] = 0;

    /* 托盘菜单刚做过操作（例如重读数据表）—— 优先显示这句，几秒后自动回到常态 */
    if (g_tray_msg[0] && (double)GetTickCount64() / 1000.0 < g_tray_msg_until) {
        snprintf(status, (size_t)scap, "%s", g_tray_msg);
        return;
    }

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

/* ---------------- 抗性表加载 / 重新加载 ---------------- */

/* 定位 + 读取抗性表。启动时和托盘菜单的"重新读取"都走这里。*/
static void load_table(void)
{
    TablePath tp;
    table_find(&tp, g_table_arg[0] ? g_table_arg : NULL, NULL, NULL);
    snwprintf_(g_res_path, MAX_PATH, L"%s", tp.path);
    snwprintf_(g_res_hint, MAX_PATH, L"%s", tp.hint);
    g_res_forced = tp.forced;
    g_res_ok = (g_res_path[0] != 0) && res_load_w(&g_res, g_res_path);
}

/* ---------------- 托盘图标 ----------------
 *
 * 面板是 WS_EX_TOOLWINDOW + WS_EX_NOACTIVATE，任务栏里不出现；
 * 关掉面板只能靠右上角的 ✕ 或 Ctrl+Alt+W。给了个托盘图标之后，
 * 用户在右下角就能找到它、退出它，也能改了数据表之后让它重读。
 */

/* ---------------- 托盘诊断日志 ----------------
 *
 * 托盘的问题（图标不出现、右键没反应）没法远程观察，所以把关键事件写到
 * 配置目录的 tray.log：每次启动重写，只有几十行。排查完可以直接删。
 * 里面记的是 hwnd / hIcon / Shell_NotifyIcon 的返回值和错误码，
 * 以及托盘回调收到的每一条消息 —— 一看就知道断在哪一步。
 */
static FILE*   g_diag;
static wchar_t g_diag_path[MAX_PATH];

static void diag_open(void)
{
    /* 放在 hr-dlc.ini 同目录，文件名换掉后缀 */
    snwprintf_(g_diag_path, MAX_PATH, L"%s", g_ini_path);
    size_t n = wcslen(g_diag_path);
    while (n > 0 && g_diag_path[n - 1] != L'\\' && g_diag_path[n - 1] != L'/') n--;
    snwprintf_(g_diag_path + n, (size_t)(MAX_PATH - n), L"tray.log");
    g_diag = _wfopen(g_diag_path, L"wb");
    if (!g_diag) return;
    fprintf(g_diag, "Ecliptica DLC tray diagnostic\n");
    fprintf(g_diag, "exe      = %s\n", TXT_EXE_NAME);
    fprintf(g_diag, "sizeof(NOTIFYICONDATAW) = %u\n", (unsigned)sizeof(NOTIFYICONDATAW));
    fprintf(g_diag, "WM_TRAY_NOTIFY = 0x%04X (WM_APP+2)\n", (unsigned)WM_TRAY_NOTIFY);
    {
        char u8[MAX_PATH * 3];
        WideCharToMultiByte(CP_UTF8, 0, g_diag_path, -1, u8, sizeof(u8), NULL, NULL);
        u8[sizeof(u8) - 1] = 0;
        fprintf(g_diag, "log file = %s\n", u8);
    }
    fflush(g_diag);
}

static void diag(const char* fmt, ...)
{
    if (!g_diag) return;
    va_list ap;
    va_start(ap, fmt);
    vfprintf(g_diag, fmt, ap);
    va_end(ap);
    fputc('\n', g_diag);
    fflush(g_diag);
}

static HICON    g_tray_icon;
static NOTIFYICONDATAW g_nid;
static bool     g_tray_added;
static int      g_tray_tries;
static DWORD    g_tray_err;     /* 最后一次 NIM_ADD 的错误码 */


/* 运行时画图标：深色底 + 青色圆点，和主程序托盘图标、面板标题栏一致。
 * 不依赖 .rc/.ico 资源，MinGW 与 MSVC 都能直接编。
 *
 * ⚠ **必须用 DIB section，不能用 CreateCompatibleBitmap**：
 * GDI 只写 RGB、从不写 alpha，32bpp 下 CreateCompatibleBitmap 得到的位图
 * alpha 全是 0，CreateIconIndirect 之后图标全透明 —— 托盘项加进去了却看不见
 * （实测 alpha 非 0 的像素 0/256）。所以自己建 DIB 并把 alpha 置 255。*/
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
    bi.bmiHeader.biHeight = -S;              /* 负高度 = 自上而下 */
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
    /* 和本体区分开：本体是蓝色圆点，DLC 用青绿色圆点，
     * 这样托盘里两个图标一眼能分清哪个是哪个。*/
    HBRUSH dot = CreateSolidBrush(RGB(110, 216, 170));
    SelectObject(dc, dot);
    SelectObject(dc, GetStockObject(NULL_PEN));
    Ellipse(dc, pad, pad, S - pad, S - pad);

    SelectObject(dc, ob);
    SelectObject(dc, op);
    DeleteObject(pen);
    DeleteObject(dot);
    SelectObject(dc, oldbmp);

    /* 补 alpha：不补就是全透明图标 */
    {
        unsigned char* px = (unsigned char*)bits;
        for (int i = 0; i < S * S; i++) px[i * 4 + 3] = 255;
    }

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

static void tray_add(void)
{
    memset(&g_nid, 0, sizeof(g_nid));
    g_nid.cbSize = sizeof(g_nid);
    g_nid.hWnd = g_hwnd;
    g_nid.uID = TRAY_UID;
    g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_nid.uCallbackMessage = WM_TRAY_NOTIFY;
    g_tray_icon = make_tray_icon();
    g_nid.hIcon = g_tray_icon ? g_tray_icon : LoadIconW(NULL, IDI_APPLICATION);
    MultiByteToWideChar(CP_UTF8, 0, TXT_TRAY_TIP, -1, g_nid.szTip,
                        (int)(sizeof(g_nid.szTip) / sizeof(g_nid.szTip[0])));
    SetLastError(0);
    g_tray_added = Shell_NotifyIconW(NIM_ADD, &g_nid) != FALSE;
    g_tray_err = g_tray_added ? 0 : GetLastError();
    diag("NIM_ADD ret=%d lastErr=%lu hwnd=0x%p hIcon=0x%p cbSize=%u uID=%u",
         (int)g_tray_added, (unsigned long)g_tray_err,
         (void*)g_nid.hWnd, (void*)g_nid.hIcon, (unsigned)g_nid.cbSize, (unsigned)g_nid.uID);
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

static HMENU tray_menu_build(void)
{
    HMENU m = CreatePopupMenu();
    if (!m) return NULL;
    wchar_t w[128];

    MultiByteToWideChar(CP_UTF8, 0, TXT_TRAY_RELOAD, -1, w, 128);
    AppendMenuW(m, MF_STRING, IDM_TRAY_RELOAD, w);

    AppendMenuW(m, MF_SEPARATOR, 0, NULL);

    MultiByteToWideChar(CP_UTF8, 0, TXT_TRAY_QUIT, -1, w, 128);
    AppendMenuW(m, MF_STRING, IDM_TRAY_QUIT, w);
    return m;
}

static void tray_command(HWND hwnd, UINT id)
{
    diag("tray command id=%u", (unsigned)id);
    switch (id) {
    case IDM_TRAY_RELOAD:
        load_table();
        refresh_view();
        snprintf(g_tray_msg, sizeof(g_tray_msg), "%s",
                 g_res_ok ? TXT_TRAY_LOADED : TXT_ST_NO_TABLE);
        g_tray_msg_until = (double)GetTickCount64() / 1000.0 + 4.0;
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case IDM_TRAY_QUIT:
        PostMessageW(hwnd, WM_CLOSE, 0, 0);
        break;
    default:
        break;
    }
}

/* 弹出托盘菜单。
 *
 * ⚠ 面板是 WS_EX_NOACTIVATE，直接 SetForegroundWindow 会失败，菜单就"没有主人"：
 * 一松手/一动鼠标就被系统关掉，看起来像菜单闪一下就没了、根本点不到。
 * 解决：临时把 NOACTIVATE 去掉，让菜单能拿到前台；菜单结束后立刻恢复，
 * 所以面板平时仍然不抢 VRChat 的焦点。
 * 选中的项用 TPM_RETURNCMD 直接取返回值，不依赖 WM_COMMAND 投递 ——
 * 非激活窗口收菜单结果并不可靠。*/
static void tray_show_menu(void)
{
    HMENU m = tray_menu_build();
    if (!m) return;

    POINT p;
    GetCursorPos(&p);

    HWND prev = GetForegroundWindow();
    LONG_PTR ex = GetWindowLongPtrW(g_hwnd, GWL_EXSTYLE);
    SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, ex & ~(LONG_PTR)WS_EX_NOACTIVATE);
    SetForegroundWindow(g_hwnd);

    UINT cmd = (UINT)TrackPopupMenu(m, TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_BOTTOMALIGN,
                                    p.x, p.y, 0, g_hwnd, NULL);
    diag("TrackPopupMenu -> %u at (%ld,%ld), prev=0x%p", (unsigned)cmd, (long)p.x, (long)p.y,
         (void*)prev);

    SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, ex);     /* 立刻恢复：不抢焦点 */
    DestroyMenu(m);
    if (prev && prev != g_hwnd && IsWindow(prev)) SetForegroundWindow(prev);
    PostMessageW(g_hwnd, WM_NULL, 0, 0);

    if (cmd) tray_command(g_hwnd, cmd);
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
        /* 开机自启时外壳可能还没就绪，Shell_NotifyIcon 会失败 —— 隔一会儿重试 */
        if (!g_tray_added && g_tray_tries < 15) {
            static int tray_tick = 0;
            if ((++tray_tick % 10) == 0) {          /* 200ms × 10 ≈ 2 秒 */
                g_tray_tries++;
                tray_add();
                if (!g_tray_added && g_tray_tries >= 15) {
                    /* 重试用尽还是失败：直接在面板上说出来，别让它静默。
                     * ERROR_ACCESS_DENIED 几乎总是"程序以低完整性运行"——
                     * 目录带 Low 标签时就会出现，换到普通目录即可。*/
                    snprintf(g_tray_msg, sizeof(g_tray_msg), "%s",
                             g_tray_err == ERROR_ACCESS_DENIED ? TXT_TRAY_DENIED
                                                               : TXT_TRAY_FAIL);
                    g_tray_msg_until = (double)GetTickCount64() / 1000.0 + 20.0;
                    diag("tray add gave up after %d tries (err=%lu)",
                         g_tray_tries, (unsigned long)g_tray_err);
                }
            }
        }
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

    case WM_TRAY_NOTIFY:
        diag("tray callback: wp=0x%p lp=0x%08lX (msg=0x%04X)",
             (void*)wp, (unsigned long)lp, (unsigned)LOWORD(lp));
        switch (LOWORD(lp)) {
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
        case WM_LBUTTONUP:          /* 左键也开菜单：右键若被外壳吞掉还有这条路 */
            tray_show_menu();
            return 0;
        case WM_LBUTTONDBLCLK:
            /* 双击：把面板提到前面（它是最顶层，但可能被全屏程序压住）*/
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        }
        return 0;

    case WM_COMMAND:
        /* 正常情况下菜单走 TPM_RETURNCMD，不会到这里；
         * 保留是为了兜住其它来源（例如以后加右键菜单到面板上）。*/
        tray_command(hwnd, (UINT)LOWORD(wp));
        return 0;

    case WM_HOTKEY:
        if (wp == HOTKEY_QUIT) PostMessageW(hwnd, WM_CLOSE, 0, 0);
        return 0;

    case WM_DESTROY:
        GetWindowRect(hwnd, &g_last_rect);
        KillTimer(hwnd, 1);
        tray_remove();
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
            } else if (arg_is(argv[i], L"table")) {
                if (i + 1 < argc) {
                    wcsncpy(g_table_arg, argv[++i], MAX_PATH - 1);
                    g_table_arg[MAX_PATH - 1] = 0;
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
    diag_open();            /* 托盘诊断日志（tray.log，与 hr-dlc.ini 同目录）*/
    /* 抗性表按 tablepath.c 里的顺序查找；--table 指定了就以它为准。
     * 必须用宽字符版本的加载器：路径里可能有中文，
     * 先转成 UTF-8 再 fopen 会被按 ANSI 代码页解释，直接打不开文件。*/
    load_table();
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
        /* 快捷键可能被别的程序占用；托盘图标才是可靠的退出口 */
        RegisterHotKey(g_hwnd, HOTKEY_QUIT, HOTKEY_ID_MOD, 'W');
        tray_add();

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
