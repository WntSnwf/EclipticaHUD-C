/* cfg.c - 配置读写（UTF-8）
 *
 * 配置文件位置分两种模式：
 *   1. 便携模式：exe 同目录已存在**可写**的 config.ini -> 就用它
 *      （把 config.ini 放在 exe 旁边即可让配置跟着程序走）
 *   2. 默认（按用户）：%APPDATA%\EclipticaHUD-C\config.ini
 *
 * 之所以默认按用户存放：exe 若装在 C:\Program Files 这类共享/只读目录，
 * 普通用户根本写不进去（x64 进程没有 UAC 虚拟化），配置会静默丢失；
 * 而放在共享可写目录时，多个 Windows 用户会互相覆盖窗口位置等设置。
 *
 * 目录名用 EclipticaHUD-C 而非 EclipticaHUD：后者是上游 Rust 版
 * EclipticaHUD 保存 pos.txt / scale.txt / top.txt / logpos.txt 的地方，
 * 分开存放可以彻底避免两份程序将来撞文件名。
 */
#include "cfg.h"
#include "evlog.h"
#include "compat.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CFG_USER_DIR L"EclipticaHUD-C"

void cfg_default(Config* c)
{
    c->always_on_top = true;
    c->alpha = 210;
    c->scale = 100;
    c->stat_window = 10;
    c->show_event_log = false;
    c->click_through = false;
    c->win_x = -1;
    c->win_y = -1;
    c->ev_filter = EVFILT_ALL;
    c->world_names[0] = 0;
}

/* exe 所在目录（含尾部反斜杠）*/
static void exe_dir_w(wchar_t* buf, int cap)
{
    wchar_t tmp[MAX_PATH];
    DWORD n = GetModuleFileNameW(NULL, tmp, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        wcsncpy(buf, L".\\", (size_t)cap - 1);
        buf[cap - 1] = 0;
        return;
    }
    tmp[n] = 0;
    wchar_t* slash = wcsrchr(tmp, L'\\');
    if (slash) slash[1] = 0;
    else wcscpy(tmp, L".\\");
    wcsncpy(buf, tmp, (size_t)cap - 1);
    buf[cap - 1] = 0;
}

/* 按用户配置目录 %APPDATA%\EclipticaHUD-C\config.ini（必要时创建目录）。
 * 取不到 %APPDATA% 时退回 %LOCALAPPDATA%。 */
static bool user_cfg_path(wchar_t* out, int cap)
{
    wchar_t base[MAX_PATH];
    DWORD n = GetEnvironmentVariableW(L"APPDATA", base, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        n = GetEnvironmentVariableW(L"LOCALAPPDATA", base, MAX_PATH);
        if (n == 0 || n >= MAX_PATH) return false;
    }

    wchar_t dir[MAX_PATH];
    snwprintf_(dir, MAX_PATH, L"%s\\%s", base, CFG_USER_DIR);
    dir[MAX_PATH - 1] = 0;
    if (!CreateDirectoryW(dir, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
        return false;                         /* 目录建不出来，交给调用方兜底 */

    snwprintf_(out, (size_t)cap, L"%s\\config.ini", dir);
    out[cap - 1] = 0;
    return true;
}

void cfg_path_w(wchar_t* buf, int cap)
{
    wchar_t dir[MAX_PATH];
    wchar_t exe_cfg[MAX_PATH];

    exe_dir_w(dir, MAX_PATH);
    snwprintf_(exe_cfg, MAX_PATH, L"%sconfig.ini", dir);
    exe_cfg[MAX_PATH - 1] = 0;

    /* 便携模式：exe 旁边已经有 config.ini 且当前用户能写 -> 就地使用。
     * 只读时（例如装在 Program Files）自动改用按用户目录。 */
    if (_waccess(exe_cfg, 0) == 0 && _waccess(exe_cfg, 2) == 0) {
        wcsncpy(buf, exe_cfg, (size_t)cap - 1);
        buf[cap - 1] = 0;
        return;
    }
    if (user_cfg_path(buf, cap)) return;

    wcsncpy(buf, exe_cfg, (size_t)cap - 1);   /* 最后兜底 */
    buf[cap - 1] = 0;
}

void cfg_path_a(char* buf, int cap)
{
    wchar_t w[MAX_PATH + 16];
    cfg_path_w(w, MAX_PATH + 16);
    WideCharToMultiByte(CP_UTF8, 0, w, -1, buf, cap, NULL, NULL);
    buf[cap - 1] = 0;
}

static void trim(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' ||
                     s[n - 1] == '\r' || s[n - 1] == '\n')) s[--n] = 0;
}

bool cfg_load(Config* c, const wchar_t* path)
{
    FILE* f = _wfopen(path, L"rb");
    if (!f) return false;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        char* eq = strchr(line, '=');
        if (!eq) continue;
        *eq = 0;
        char* k = line;
        while (*k == ' ' || *k == '\t') k++;
        trim(k);
        char* v = eq + 1;
        while (*v == ' ' || *v == '\t') v++;
        trim(v);
        if (k[0] == '#' || k[0] == '\0') continue;
        if (!strcmp(k, "always_on_top")) c->always_on_top = atoi(v) != 0;
        else if (!strcmp(k, "alpha")) c->alpha = atoi(v);
        else if (!strcmp(k, "scale")) c->scale = atoi(v);
        else if (!strcmp(k, "stat_window")) c->stat_window = atoi(v);
        else if (!strcmp(k, "show_event_log")) c->show_event_log = atoi(v) != 0;
        else if (!strcmp(k, "click_through")) c->click_through = atoi(v) != 0;
        else if (!strcmp(k, "win_x")) c->win_x = atoi(v);
        else if (!strcmp(k, "win_y")) c->win_y = atoi(v);
        else if (!strcmp(k, "ev_filter")) c->ev_filter = atoi(v);
        else if (!strcmp(k, "world_names")) {
            strncpy(c->world_names, v, sizeof(c->world_names) - 1);
            c->world_names[sizeof(c->world_names) - 1] = 0;
        }
    }
    fclose(f);

    if (c->alpha < CFG_ALPHA_MIN) c->alpha = CFG_ALPHA_MIN;
    if (c->alpha > CFG_ALPHA_MAX) c->alpha = CFG_ALPHA_MAX;
    if (c->scale < CFG_SCALE_MIN) c->scale = CFG_SCALE_MIN;
    if (c->scale > CFG_SCALE_MAX) c->scale = CFG_SCALE_MAX;
    if (c->stat_window != 3 && c->stat_window != 5 && c->stat_window != 10 &&
        c->stat_window != 30 && c->stat_window != 60 && c->stat_window != 120)
        c->stat_window = 10;
    if (c->ev_filter < 0 || c->ev_filter >= EVFILT_COUNT) c->ev_filter = EVFILT_ALL;
    return true;
}

/* config.ini 以 UTF-8 写出；注释用 ASCII，避免不同编译器源码编码差异。
 * 返回 false 表示写不进去（调用方可以选择提示用户）。 */
bool cfg_save(const Config* c, const wchar_t* path)
{
    FILE* f = _wfopen(path, L"wb");
    if (!f) return false;
    fprintf(f, "# Ecliptica HUD (C) config - UTF-8\n");
    fprintf(f, "always_on_top=%d\n", c->always_on_top ? 1 : 0);
    fprintf(f, "alpha=%d\n", c->alpha);
    fprintf(f, "scale=%d\n", c->scale);
    fprintf(f, "stat_window=%d\n", c->stat_window);
    fprintf(f, "show_event_log=%d\n", c->show_event_log ? 1 : 0);
    fprintf(f, "click_through=%d\n", c->click_through ? 1 : 0);
    fprintf(f, "win_x=%d\n", c->win_x);
    fprintf(f, "win_y=%d\n", c->win_y);
    fprintf(f, "ev_filter=%d\n", c->ev_filter);
    fprintf(f, "# world_names: extra Ecliptica-family world names, separated by | or ,\n");
    fprintf(f, "world_names=%s\n", c->world_names);
    fclose(f);
    return true;
}
