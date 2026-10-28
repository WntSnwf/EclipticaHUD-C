/* vlog.c - 定位并增量跟随 VRChat 日志
 *
 * 定位优先级：
 *   1. --log 指定文件
 *   2. VRChat 自己的日志目录（两种命名都覆盖，取"最后写入时间最新"的一个）
 *        %USERPROFILE%\AppData\LocalLow\VRChat\VRChat\output_log.txt
 *        %USERPROFILE%\AppData\LocalLow\VRChat\VRChat\output_log_YYYY-MM-DD_HH-MM-SS.txt
 *      现版本 VRChat 只写带时间戳的那种（每次会话一个文件），旧版本写
 *      output_log.txt，所以必须用 output_log*.txt 通配匹配，不能只试固定名。
 *   3. exe 同目录 / 当前目录 / exe 上级目录 里的 output_log*.txt
 *      仅当第 2 步一个都没找到时才用，方便"把 exe 丢到日志旁边"离线回放。
 */
#include "vlog.h"
#include "compat.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

struct VLog {
    FILE*   f;
    wchar_t path[MAX_PATH];
    wchar_t forced[MAX_PATH];  /* --log 指定的路径（仅 forced_only 时有效） */
    bool    forced_only;       /* true = 只用指定文件，绝不回退到自动定位 */
    int     status;          /* 0 = 未连接，1 = 已连接 */
    bool    demo;
    bool    from_start;
    DWORD   last_scan;       /* 上次重新定位的时间 */
    DWORD   demo_tick;       /* 演示模式节流 */
    int     demo_i;
    int     demo_base;
    bool    reopened;
};

#define RESCAN_MS 2000
#define DEMO_MS   45         /* 演示模式每 45ms 产出一行，节奏接近真实日志 */

/* ---------------- 文件定位 ---------------- */

/* 在 dir（需以反斜杠结尾）下找 output_log*.txt 中最后写入时间最新的一个。
 * 通配同时覆盖 output_log.txt 和 output_log_2026-09-23_13-26-55.txt。 */
static bool newest_in_dir(const wchar_t* dir, wchar_t* out, int cap, FILETIME* out_t)
{
    wchar_t pat[MAX_PATH];
    snwprintf_(pat, MAX_PATH, L"%soutput_log*.txt", dir);
    pat[MAX_PATH - 1] = 0;

    wchar_t best[MAX_PATH];
    FILETIME best_t;
    bool have = false;
    best[0] = 0;

    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW(pat, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
            if (!have || CompareFileTime(&fd.ftLastWriteTime, &best_t) > 0) {
                snwprintf_(best, MAX_PATH, L"%s%s", dir, fd.cFileName);
                best[MAX_PATH - 1] = 0;
                best_t = fd.ftLastWriteTime;
                have = true;
            }
        } while (FindNextFileW(h, &fd));
        FindClose(h);
    }
    if (!have) { out[0] = 0; return false; }
    wcsncpy(out, best, (size_t)cap - 1);
    out[cap - 1] = 0;
    if (out_t) *out_t = best_t;
    return true;
}

static bool ends_with_ci(const wchar_t* s, const wchar_t* suffix)
{
    size_t ls = wcslen(s), lf = wcslen(suffix);
    if (ls < lf) return false;
    for (size_t i = 0; i < lf; i++) {
        wchar_t a = s[ls - lf + i];
        if (a >= L'A' && a <= L'Z') a = (wchar_t)(a - L'A' + L'a');
        if (a != suffix[i]) return false;
    }
    return true;
}

static void add_dir(wchar_t dirs[][MAX_PATH], int* n, int max, const wchar_t* d)
{
    if (*n >= max || !d || !d[0]) return;
    for (int i = 0; i < *n; i++)
        if (!_wcsicmp(dirs[i], d)) return;          /* 去重 */
    wcsncpy(dirs[*n], d, MAX_PATH - 1);
    dirs[*n][MAX_PATH - 1] = 0;
    (*n)++;
}

/* VRChat 日志目录：%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\ */
static int vrchat_dirs(wchar_t dirs[][MAX_PATH])
{
    int n = 0;
    wchar_t buf[MAX_PATH];
    DWORD r;

    r = GetEnvironmentVariableW(L"USERPROFILE", buf, MAX_PATH);
    if (r > 0 && r < MAX_PATH) {
        wchar_t d[MAX_PATH];
        snwprintf_(d, MAX_PATH, L"%s\\AppData\\LocalLow\\VRChat\\VRChat\\", buf);
        d[MAX_PATH - 1] = 0;
        add_dir(dirs, &n, 2, d);
    }

    /* USERPROFILE 被重定向时的兜底：%LOCALAPPDATA% = ...\AppData\Local */
    r = GetEnvironmentVariableW(L"LOCALAPPDATA", buf, MAX_PATH);
    if (r > 0 && r < MAX_PATH && ends_with_ci(buf, L"\\Local")) {
        wchar_t d[MAX_PATH];
        buf[wcslen(buf) - 6] = 0;                   /* 去掉 "\Local" */
        snwprintf_(d, MAX_PATH, L"%s\\LocalLow\\VRChat\\VRChat\\", buf);
        d[MAX_PATH - 1] = 0;
        add_dir(dirs, &n, 2, d);
    }
    return n;
}

static void exe_dir(wchar_t* out, int cap)
{
    DWORD n = GetModuleFileNameW(NULL, out, (DWORD)cap);
    if (n == 0 || n >= (DWORD)cap) { out[0] = 0; return; }
    wchar_t* slash = wcsrchr(out, L'\\');
    if (slash) slash[1] = 0; else out[0] = 0;
}

/* exe 同目录 / 当前目录 / exe 上级目录（均带尾反斜杠）*/
static int local_dirs(wchar_t dirs[][MAX_PATH])
{
    int n = 0;
    wchar_t exe[MAX_PATH];
    exe_dir(exe, MAX_PATH);
    add_dir(dirs, &n, 3, exe);

    wchar_t cwd[MAX_PATH];
    DWORD cw = GetCurrentDirectoryW(MAX_PATH, cwd);
    if (cw > 0 && cw < MAX_PATH) {
        size_t l = wcslen(cwd);
        if (l + 1 < MAX_PATH) { cwd[l] = L'\\'; cwd[l + 1] = 0; }
        add_dir(dirs, &n, 3, cwd);
    }

    if (exe[0]) {
        wchar_t up[MAX_PATH];
        wcsncpy(up, exe, MAX_PATH - 1);
        up[MAX_PATH - 1] = 0;
        size_t l = wcslen(up);
        if (l > 3) {
            up[l - 1] = 0;                          /* 去掉尾部反斜杠 */
            wchar_t* slash = wcsrchr(up, L'\\');
            if (slash) {
                slash[1] = 0;
                add_dir(dirs, &n, 3, up);
            }
        }
    }
    return n;
}

static bool find_log(wchar_t* out, int cap)
{
    wchar_t best[MAX_PATH];
    FILETIME best_t;
    out[0] = 0;

    /* 第一优先：VRChat 日志目录，找到即用 */
    wchar_t vdirs[2][MAX_PATH];
    int nv = vrchat_dirs(vdirs);
    for (int i = 0; i < nv; i++) {
        if (newest_in_dir(vdirs[i], best, MAX_PATH, &best_t)) {
            wcsncpy(out, best, (size_t)cap - 1);
            out[cap - 1] = 0;
            return true;
        }
    }

    /* 第二优先：exe 附近，取其中最新的一个 */
    wchar_t cdirs[3][MAX_PATH];
    int nc = local_dirs(cdirs);
    bool have = false;
    for (int i = 0; i < nc; i++) {
        wchar_t cand[MAX_PATH];
        FILETIME ct;
        if (!newest_in_dir(cdirs[i], cand, MAX_PATH, &ct)) continue;
        if (!have || CompareFileTime(&ct, &best_t) > 0) {
            wcsncpy(best, cand, MAX_PATH - 1);
            best[MAX_PATH - 1] = 0;
            best_t = ct;
            have = true;
        }
    }
    if (!have) return false;
    wcsncpy(out, best, (size_t)cap - 1);
    out[cap - 1] = 0;
    return true;
}

/* ---------------- 打开 / 定位 ---------------- */

static void seek_to_tail(FILE* f)
{
    if (fseek(f, 0, SEEK_END) != 0) return;
    long size = ftell(f);
    if (size <= 0) { fseek(f, 0, SEEK_SET); return; }
    long back = size < 65536 ? size : 65536;
    fseek(f, size - back, SEEK_SET);
    /* 丢弃可能被截断的第一行 */
    int c;
    while ((c = fgetc(f)) != EOF)
        if (c == '\n') break;
    clearerr(f);
}

static bool try_open(VLog* v, const wchar_t* path)
{
    FILE* f = _wfopen(path, L"rb");
    if (!f) return false;
    if (v->f) fclose(v->f);
    v->f = f;
    wcsncpy(v->path, path, MAX_PATH - 1);
    v->path[MAX_PATH - 1] = 0;
    if (v->from_start) fseek(f, 0, SEEK_SET);
    else seek_to_tail(f);
    v->status = 1;
    return true;
}

VLog* vlog_open(const wchar_t* forced, bool demo, bool from_start)
{
    VLog* v = (VLog*)calloc(1, sizeof(VLog));
    if (!v) return NULL;
    v->demo = demo;
    v->from_start = from_start;
    if (demo) { v->status = 1; return v; }

    if (forced && forced[0]) {
        /* 指定了文件就只用它：绝不悄悄退回到别的日志，否则用户会看到
         * 一份完全不相干的数据（这个坑实测踩过）。 */
        wcsncpy(v->forced, forced, MAX_PATH - 1);
        v->forced[MAX_PATH - 1] = 0;
        v->forced_only = true;
        if (try_open(v, forced)) return v;
        v->status = 0;
        return v;
    }
    wchar_t p[MAX_PATH];
    if (find_log(p, MAX_PATH) && try_open(v, p)) return v;
    v->status = 0;
    return v;
}

void vlog_close(VLog* v)
{
    if (!v) return;
    if (v->f) fclose(v->f);
    free(v);
}

int vlog_status(const VLog* v) { return v ? v->status : 0; }

bool vlog_forced_only(const VLog* v) { return v ? v->forced_only : false; }

const wchar_t* vlog_path(const VLog* v) { return v ? v->path : L""; }

bool vlog_take_rotated(VLog* v)
{
    if (!v) return false;
    bool r = v->reopened;
    v->reopened = false;
    return r;
}

/* ---------------- 演示模式 ---------------- */

/* 按真实日志格式合成剧本，解析器与正常运行时完全一致 */
static const char* DEMO_SCRIPT[] = {
    "ECLIPTICA Loading Settings...",
    "ECLIPTICA loaded blank session ID.",
    "ECLIPTICA - now in stage: Stage_Hall of Beginnings on phase: 0 as class: Spellhammer",
    "spawn token, False, 0",
    "spawn token, True, 55",
    "ECLIPTICA saving SESSION ID 11508",
    "Dealing 120 STRIKE damage",
    "Dealing 45 NON-STRIKE damage",
    "damage has been taken: 12, from source: (Khepri) attack_Claws2",
    "Dealing 96 STRIKE damage",
    "ECLIPTICA - now fighting boss: ObisidusPhase2(Clone) on phase: 0.7223684",
    "Dealing 310 STRIKE damage",
    "damage has been taken: 43, from source: (Peltapod) attack_Slam",
    "Dealing 480 STRIKE damage",
    "Dealing 220 NON-STRIKE damage",
    "damage has been taken: 118, from source: attack_Spit (2)",
    "damage has been taken: 8, from source: machinegunShooter2",
    "Dealing 512 STRIKE damage",
    "ownership of ObisidusPhase2 transferred to OtherPlayer",
    "Dealing 260 STRIKE damage",
    "Local controller dead, switching off.",
    "damage has been taken: 300, from source: NukeHitbox (BIG)",
    "Boss ObisidusPhase2 dead, personal damage dealt: ",
    "STRIKE DMG: 4793",
    "NON-STRIKE DMG: 615",
    "ECLIPTICA - now in intermission",
    "ECLIPTICA - now in stage: Stage_ProtoColony on phase: 0.1220348 as class: Nekomancer",
    "spawn token, False, 0",
    "ECLIPTICA saving SESSION ID 11508",
    "Dealing 88 STRIKE damage",
    "damage has been taken: 21, from source: (Yuki) frostBeam",
    "ECLIPTICA - now fighting boss: FlyLord(Clone) on phase: 0.06045651",
    "Dealing 640 STRIKE damage",
    "Dealing 305 NON-STRIKE damage",
    "damage has been taken: 55, from source: ([Missing Key \"e_VirtueBeam\"]) damageTick",
    "Boss FlyLord dead, personal damage dealt: ",
    "STRIKE DMG: 8120",
    "NON-STRIKE DMG: 900",
    "ECLIPTICA - now in lobby",
};
#define DEMO_N ((int)(sizeof(DEMO_SCRIPT) / sizeof(DEMO_SCRIPT[0])))

static int demo_emit(VLog* v, char* line, int cap)
{
    int base_min = (v->demo_base * 7) % 60;
    if (v->demo_i == 0) {
        snprintf_(line, (size_t)cap,
                  "2026.09.22 20:%02d:00 Debug      -  [Behaviour] Joining wrld_0fb88df3-2057-4c2f-8e06-e948864378fd:87887~region(use)",
                  base_min);
        v->demo_i++;
        return 1;
    }
    if (v->demo_i == 1) {
        snprintf_(line, (size_t)cap,
                  "2026.09.22 20:%02d:01 Debug      -  [Behaviour] Entering Room: Ecliptica - Demo Playtest",
                  base_min);
        v->demo_i++;
        return 1;
    }
    int idx = v->demo_i - 2;
    if (idx >= DEMO_N) {
        snprintf_(line, (size_t)cap, "2026.09.22 20:%02d:59 Debug      -  [Behaviour] OnLeftRoom",
                  base_min);
        v->demo_i = 0;
        v->demo_base++;
        return 1;
    }
    int total_sec = 2 + idx * 3;
    int mm = (base_min + total_sec / 60) % 60;
    int ss = total_sec % 60;
    snprintf_(line, (size_t)cap, "2026.09.22 20:%02d:%02d Debug      -  %s", mm, ss, DEMO_SCRIPT[idx]);
    v->demo_i++;
    return 1;
}

/* ---------------- 轮询 ---------------- */

int vlog_poll(VLog* v, char* line, int cap)
{
    if (!v) return -1;
    if (v->demo) {
        DWORD now = GetTickCount();
        if (v->demo_tick && now - v->demo_tick < DEMO_MS) return 0;
        v->demo_tick = now ? now : 1;
        return demo_emit(v, line, cap);
    }

    DWORD now = GetTickCount();
    if (!v->f) {
        if (now - v->last_scan < RESCAN_MS) { v->status = 0; return -1; }
        v->last_scan = now;
        if (v->forced_only) {
            /* 只重试用户指定的文件（比如 VRChat 稍后才创建它）*/
            if (try_open(v, v->forced)) { v->reopened = true; return 0; }
            v->status = 0;
            return -1;
        }
        wchar_t p[MAX_PATH];
        if (find_log(p, MAX_PATH) && try_open(v, p)) { v->reopened = true; return 0; }
        v->status = 0;
        return -1;
    }

    if (fgets(line, cap, v->f)) {
        size_t n = strlen(line);
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r')) line[--n] = 0;
        return 1;
    }

    clearerr(v->f);

    if (now - v->last_scan >= RESCAN_MS) {
        v->last_scan = now;
        long cur = ftell(v->f);
        bool rotated = false;

        if (v->forced_only) {
            /* 指定文件：只判断它本身是否被删除或截断，不切换到别的日志 */
            FILE* chk = _wfopen(v->forced, L"rb");
            if (!chk) {
                rotated = true;
            } else {
                fseek(chk, 0, SEEK_END);
                long sz = ftell(chk);
                fclose(chk);
                if (cur >= 0 && sz < cur) rotated = true;
            }
            if (rotated) {
                if (v->f) { fclose(v->f); v->f = NULL; }
                if (try_open(v, v->forced)) { v->reopened = true; return 0; }
                v->status = 0;
                return -1;
            }
            return v->status ? 0 : -1;
        }

        wchar_t p[MAX_PATH];
        if (find_log(p, MAX_PATH)) {
            if (wcscmp(p, v->path) != 0) rotated = true;
        }
        long sz = -1;
        {
            FILE* chk = _wfopen(v->path, L"rb");
            if (chk) { fseek(chk, 0, SEEK_END); sz = ftell(chk); fclose(chk); }
            else rotated = true;                        /* 文件被删除/替换 */
        }
        if (!rotated && sz >= 0 && cur >= 0 && sz < cur) rotated = true;
        if (rotated) {
            if (v->f) { fclose(v->f); v->f = NULL; }
            const wchar_t* target = (find_log(p, MAX_PATH) && p[0]) ? p : v->path;
            if (try_open(v, target)) { v->reopened = true; return 0; }
            v->status = 0;
            return -1;
        }
    }
    return v->status ? 0 : -1;
}
