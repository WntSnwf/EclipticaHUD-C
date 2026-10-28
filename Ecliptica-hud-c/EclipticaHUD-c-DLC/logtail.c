/* logtail.c - 日志定位 / 跟随 / 当前 Boss 识别 */
#include "logtail.h"
#include "res.h"
#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- 时间 ---------------- */

static double now_s(void)
{
    return (double)GetTickCount64() / 1000.0;
}

/* ---------------- 日志定位 ---------------- */

/* 在 dir 里找最后写入时间最新的 output_log*.txt */
static bool newest_in_dir(const wchar_t* dir, wchar_t* out, int cap)
{
    wchar_t pat[MAX_PATH];
    snwprintf_(pat, MAX_PATH, L"%s\\output_log*.txt", dir);

    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW(pat, &fd);
    if (h == INVALID_HANDLE_VALUE) return false;

    ULARGE_INTEGER best;
    best.QuadPart = 0;
    bool found = false;
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        ULARGE_INTEGER t;
        t.LowPart = fd.ftLastWriteTime.dwLowDateTime;
        t.HighPart = fd.ftLastWriteTime.dwHighDateTime;
        if (!found || t.QuadPart > best.QuadPart) {
            best = t;
            snwprintf_(out, (size_t)cap, L"%s\\%s", dir, fd.cFileName);
            found = true;
        }
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    return found;
}

static void exe_dir(wchar_t* out, int cap)
{
    wchar_t tmp[MAX_PATH];
    DWORD n = GetModuleFileNameW(NULL, tmp, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) { snwprintf_(out, (size_t)cap, L"."); return; }
    wchar_t* slash = wcsrchr(tmp, L'\\');
    if (slash) *slash = 0;
    snwprintf_(out, (size_t)cap, L"%s", tmp);
}

/* 定位顺序与本体一致：VRChat 日志目录 -> exe 同目录 -> 当前目录 */
static bool find_log(wchar_t* out, int cap)
{
    wchar_t dir[MAX_PATH];

    DWORD n = GetEnvironmentVariableW(L"USERPROFILE", dir, MAX_PATH);
    if (n > 0 && n < MAX_PATH) {
        wchar_t p[MAX_PATH];
        snwprintf_(p, MAX_PATH, L"%s\\AppData\\LocalLow\\VRChat\\VRChat", dir);
        if (newest_in_dir(p, out, cap)) return true;
    }
    n = GetEnvironmentVariableW(L"LOCALAPPDATA", dir, MAX_PATH);
    if (n > 0 && n < MAX_PATH) {
        wchar_t p[MAX_PATH];
        snwprintf_(p, MAX_PATH, L"%s\\..\\LocalLow\\VRChat\\VRChat", dir);
        if (newest_in_dir(p, out, cap)) return true;
    }

    exe_dir(dir, MAX_PATH);
    if (newest_in_dir(dir, out, cap)) return true;
    if (newest_in_dir(L".", out, cap)) return true;
    return false;
}

/* ---------------- Boss 识别 ---------------- */

/* 从 "ECLIPTICA - now fighting boss: YukiPhase2(Clone) on phase: 0.6"
 * 里取出内部名。返回 false 表示这行不是开战行。 */
static bool parse_boss_line(const char* line, char* name, int cap, int* phase)
{
    static const char* MARK = "now fighting boss: ";
    const char* p = strstr(line, MARK);
    if (!p) return false;
    p += strlen(MARK);

    const char* end = strstr(p, " on phase:");
    char raw[96];
    size_t n = end ? (size_t)(end - p) : strlen(p);
    if (n >= sizeof(raw)) n = sizeof(raw) - 1;
    memcpy(raw, p, n);
    raw[n] = 0;

    char* cr = strstr(raw, "\r");
    if (cr) *cr = 0;

    res_boss_base(raw, name, cap);        /* 去掉 (Clone) / PhaseN */
    *phase = res_boss_phase(raw);
    return name[0] != 0;
}

/* 处理一行，返回 true 表示当前 Boss 状态有变化 */
static bool feed_line(LogTail* lt, const char* line)
{
    char nm[64];
    int  ph = 1;
    char prev[64];
    int  prev_ph = lt->phase;
    bool prev_in = lt->in_fight;
    snprintf(prev, sizeof(prev), "%s", lt->boss);

    if (parse_boss_line(line, nm, sizeof(nm), &ph)) {
        snprintf(lt->boss, sizeof(lt->boss), "%s", nm);
        lt->phase = ph;
        lt->in_fight = true;
        return strcmp(prev, lt->boss) != 0 || prev_ph != ph || !prev_in;
    }

    /* Boss 被击杀。
     *
     * 这里必须**连形态号一起比**，不能只比基础名 —— 实测日志里多形态 Boss 的
     * 击杀行会迟到，而且迟到的是上一个形态的：
     *     7204  now fighting boss: JimBringerPhase3(Clone) ...   <- P3 已经开打
     *     7222  Boss JimBringerPhase2 dead, personal damage dealt:  <- 18 行之后才来的 P2 击杀
     * 只比基础名的话，这一行会把正在进行的 P3 一起清掉，表现就是
     * 「Jim(P3) 的抗性一直不显示」。*/
    {
        static const char* DEAD = " dead, personal damage dealt:";
        const char* d = strstr(line, DEAD);
        if (d && lt->in_fight) {
            const char* name_start = NULL;
            if (!strncmp(line, "Boss ", 5)) name_start = line + 5;
            else {
                /* 行首带时间戳时，找最后一个 "Boss " */
                const char* b = strstr(line, "Boss ");
                if (b) name_start = b + 5;
            }
            if (name_start) {
                char dead_name[96];
                size_t n = (size_t)(d - name_start);
                if (n >= sizeof(dead_name)) n = sizeof(dead_name) - 1;
                memcpy(dead_name, name_start, n);
                dead_name[n] = 0;

                int  dph = res_boss_phase(dead_name);   /* 无 PhaseN 后缀 = 1 */
                char db[64];
                res_boss_base(dead_name, db, sizeof(db));

                if (!strcmp(db, lt->boss) && dph == lt->phase) {
                    lt->in_fight = false;
                    return true;
                }
            }
        }
    }

    /* 这些行一出现就说明这一场结束了 */
    if (strstr(line, "now in intermission") || strstr(line, "now in lobby") ||
        strstr(line, "now in stage:") ||
        strstr(line, "[Behaviour] Entering Room:") ||
        strstr(line, "[Behaviour] OnLeftRoom") ||
        strstr(line, "VRCApplication: HandleApplicationQuit")) {
        if (lt->in_fight || lt->boss[0]) {
            lt->in_fight = false;
            lt->boss[0] = 0;
            lt->phase = 1;
            return true;
        }
    }
    return false;
}

/* 把文件从头读到尾（或只读新增部分） */
static long drain(LogTail* lt)
{
    if (!lt->f) return 0;
    char line[4096];
    long n = 0;
    while (fgets(line, sizeof(line), lt->f)) {
        size_t l = strlen(line);
        while (l > 0 && (line[l - 1] == '\n' || line[l - 1] == '\r')) line[--l] = 0;
        if (!line[0]) continue;
        feed_line(lt, line);
        n++;
    }
    clearerr(lt->f);
    return n;
}

static bool try_open(LogTail* lt, const wchar_t* path)
{
    FILE* f = _wfopen(path, L"rb");
    if (!f) return false;
    if (lt->f) fclose(lt->f);
    lt->f = f;
    snwprintf_(lt->path, MAX_PATH, L"%s", path);
    lt->ready = true;
    /* 从头扫一遍：HUD 常常是在战斗中途才启动的，只看新增行会不知道当前 Boss */
    drain(lt);
    return true;
}

void logtail_open(LogTail* lt, const wchar_t* forced)
{
    memset(lt, 0, sizeof(*lt));
    lt->phase = 1;
    if (forced && forced[0]) {
        lt->forced = true;
        if (!try_open(lt, forced)) {
            lt->ready = false;
            lt->path[0] = 0;
        }
        return;
    }
    wchar_t p[MAX_PATH];
    if (find_log(p, MAX_PATH)) try_open(lt, p);
    lt->rescan_t = now_s();
}

bool logtail_poll(LogTail* lt)
{
    bool changed = false;

    /* 日志轮换：VRChat 每次会话写一个新文件，定期重新找最新的那个 */
    if (!lt->forced) {
        double t = now_s();
        if (t - lt->rescan_t >= 2.0) {
            lt->rescan_t = t;
            wchar_t p[MAX_PATH];
            if (find_log(p, MAX_PATH)) {
                if (wcscmp(p, lt->path) != 0) {
                    if (try_open(lt, p)) changed = true;
                } else if (!lt->f) {
                    if (try_open(lt, p)) changed = true;
                }
            }
        }
    } else if (!lt->f) {
        /* --log 指定的文件当时打不开：每 2 秒重试 */
        double t = now_s();
        if (t - lt->rescan_t >= 2.0) {
            lt->rescan_t = t;
            if (try_open(lt, lt->path)) changed = true;
        }
    }

    if (!lt->f) return changed;

    char before[64];
    int  before_ph = lt->phase;
    bool before_in = lt->in_fight;
    snprintf(before, sizeof(before), "%s", lt->boss);

    if (drain(lt) > 0) {
        if (strcmp(before, lt->boss) != 0 || before_ph != lt->phase || before_in != lt->in_fight)
            changed = true;
    }
    return changed;
}

void logtail_close(LogTail* lt)
{
    if (lt->f) fclose(lt->f);
    lt->f = NULL;
}

void logtail_name(const LogTail* lt, char* out, int cap)
{
    out[0] = 0;
    if (!lt->path[0]) return;
    const wchar_t* base = wcsrchr(lt->path, L'\\');
    base = base ? base + 1 : lt->path;
    WideCharToMultiByte(CP_UTF8, 0, base, -1, out, cap, NULL, NULL);
    out[cap - 1] = 0;
}

bool logtail_ready(const LogTail* lt)
{
    return lt->f != NULL;
}
