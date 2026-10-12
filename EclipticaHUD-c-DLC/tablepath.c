/* tablepath.c - 抗性表查找 */
#include "tablepath.h"
#include "compat.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>

static bool file_exists(const wchar_t* p)
{
    FILE* f = _wfopen(p, L"rb");
    if (!f) return false;
    fclose(f);
    return true;
}

/* 把路径规整成绝对路径（去掉 .. 之类），纯粹为了显示好看 */
static void normalize(const wchar_t* in, wchar_t* out, int cap)
{
    wchar_t tmp[MAX_PATH];
    DWORD n = GetFullPathNameW(in, MAX_PATH, tmp, NULL);
    if (n == 0 || n >= MAX_PATH) { snwprintf_(out, (size_t)cap, L"%s", in); return; }
    snwprintf_(out, (size_t)cap, L"%s", tmp);
}

static void self_exe_dir(wchar_t* out, int cap)
{
    wchar_t tmp[MAX_PATH];
    DWORD n = GetModuleFileNameW(NULL, tmp, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) { snwprintf_(out, (size_t)cap, L"."); return; }
    wchar_t* slash = wcsrchr(tmp, L'\\');
    if (slash) *slash = 0;
    snwprintf_(out, (size_t)cap, L"%s", tmp);
}

/* dir\sub\表 或 dir\表 */
static bool probe(TablePath* tp, const wchar_t* dir, const wchar_t* sub)
{
    if (!dir || !dir[0]) return false;
    wchar_t p[MAX_PATH];
    if (sub && sub[0]) snwprintf_(p, MAX_PATH, L"%s\\%s\\%s", dir, sub, TABLE_FILE_NAME);
    else               snwprintf_(p, MAX_PATH, L"%s\\%s", dir, TABLE_FILE_NAME);
    if (!file_exists(p)) return false;
    normalize(p, tp->path, MAX_PATH);
    return true;
}

void table_find(TablePath* tp, const wchar_t* forced,
                const wchar_t* exe_dir_in, const wchar_t* cwd_in)
{
    memset(tp, 0, sizeof(*tp));

    wchar_t exe[MAX_PATH], cwd[MAX_PATH], up[MAX_PATH];

    if (exe_dir_in && exe_dir_in[0]) {
        wcsncpy(exe, exe_dir_in, MAX_PATH - 1);
        exe[MAX_PATH - 1] = 0;
    } else {
        self_exe_dir(exe, MAX_PATH);
    }
    normalize(exe, exe, MAX_PATH);

    if (cwd_in) {
        wcsncpy(cwd, cwd_in, MAX_PATH - 1);
        cwd[MAX_PATH - 1] = 0;
    } else if (!_wgetcwd(cwd, MAX_PATH)) {
        cwd[0] = 0;
    }

    /* 找不到时建议用户放在 exe 旁边 —— 最直观的位置 */
    snwprintf_(tp->hint, MAX_PATH, L"%s", exe);

    /* 1. --table：指定了就不回退，找不到就是找不到（免得用户以为生效了）*/
    if (forced && forced[0]) {
        tp->forced = true;
        normalize(forced, tp->path, MAX_PATH);
        if (!file_exists(tp->path)) tp->path[0] = 0;
        return;
    }

    snwprintf_(up, MAX_PATH, L"%s\\..", exe);

    if (probe(tp, exe, NULL))         return;   /* 2 */
    if (probe(tp, exe, TABLE_SUBDIR)) return;   /* 3 */
    if (probe(tp, up,  NULL))         return;   /* 4 */
    if (probe(tp, up,  TABLE_SUBDIR)) return;   /* 5 */
    if (probe(tp, cwd, NULL))         return;   /* 6 */
    if (probe(tp, cwd, TABLE_SUBDIR)) return;   /* 7 */
}
