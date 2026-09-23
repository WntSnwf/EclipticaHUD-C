/* cfg.c - 配置读写（exe 同目录 config.ini，UTF-8）*/
#include "cfg.h"
#include "evlog.h"
#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cfg_default(Config* c)
{
    c->always_on_top = true;
    c->alpha = 210;
    c->scale = 100;
    c->stat_window = 10;
    c->show_event_log = false;
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

void cfg_path_w(wchar_t* buf, int cap)
{
    exe_dir_w(buf, cap);
    size_t used = wcslen(buf);
    if (used + 11 < (size_t)cap) wcscat(buf, L"config.ini");
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

/* config.ini 以 UTF-8 写出；注释用 ASCII，避免不同编译器源码编码差异 */
void cfg_save(const Config* c, const wchar_t* path)
{
    FILE* f = _wfopen(path, L"wb");
    if (!f) return;
    fprintf(f, "# Ecliptica HUD (C) config - UTF-8\n");
    fprintf(f, "always_on_top=%d\n", c->always_on_top ? 1 : 0);
    fprintf(f, "alpha=%d\n", c->alpha);
    fprintf(f, "scale=%d\n", c->scale);
    fprintf(f, "stat_window=%d\n", c->stat_window);
    fprintf(f, "show_event_log=%d\n", c->show_event_log ? 1 : 0);
    fprintf(f, "win_x=%d\n", c->win_x);
    fprintf(f, "win_y=%d\n", c->win_y);
    fprintf(f, "ev_filter=%d\n", c->ev_filter);
    fprintf(f, "# world_names: extra Ecliptica-family world names, separated by | or ,\n");
    fprintf(f, "world_names=%s\n", c->world_names);
    fclose(f);
}
