/* main.c - Ecliptica HUD (C) 入口
 *
 * 用法：
 *   ecliptica-hud-c.exe                  跟随 VRChat 实时日志
 *   ecliptica-hud-c.exe --demo           演示模式（内置真实格式的模拟日志）
 *   ecliptica-hud-c.exe --log 文件       回放指定日志（从头解析，并继续跟随新增行）
 *   ecliptica-hud-c.exe --from-start     从头读完整份日志（默认只从末尾附近开始）
 *   ecliptica-hud-c.exe --tail           从末尾附近开始（默认行为，用于覆盖前面的设置）
 *   ecliptica-hud-c.exe --help           显示本帮助
 *
 * 参数大小写不敏感，--demo 与 -demo、--DEMO 等价。
 * 认不出来的参数会弹出帮助而不是被静默忽略 —— 实测有用户把 --demo 写成 --Demo，
 * 结果程序当作普通启动去读了真实日志，界面上完全看不出哪里错了。
 */
#include "cfg.h"
#include "names.h"
#include "overlay.h"
#include "compat.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

/* 匹配 --name / -name，大小写不敏感（Windows 命令行惯例）*/
static bool arg_is(const wchar_t* a, const wchar_t* name)
{
    if (!a || a[0] != L'-') return false;
    a += (a[1] == L'-') ? 2 : 1;
    return _wcsicmp(a, name) == 0;
}

static void show_help(void)
{
    const char* msg =
        "Ecliptica HUD (C)\n"
        "\n"
        "参数不分大小写：--demo / -demo / --DEMO 都可以。\n"
        "\n"
        "  ecliptica-hud-c.exe               跟随 VRChat 实时日志（从末尾附近开始）\n"
        "  ecliptica-hud-c.exe --demo        演示模式（无需 VRChat，内置模拟事件）\n"
        "  ecliptica-hud-c.exe --log FILE    回放指定日志文件，并继续跟随新增内容\n"
        "  ecliptica-hud-c.exe --from-start  从开头读完整份日志\n"
        "  ecliptica-hud-c.exe --tail        从末尾附近开始（默认行为）\n"
        "  ecliptica-hud-c.exe --help        显示本帮助\n"
        "\n"
        "提示：请把 --log 写在最后。若写成 \"--log FILE --tail\"，\n"
        "      回放会退化成只读该文件最后 64 KB。\n"
        "\n"
        "日志自动定位顺序：\n"
        "  1) 取最后写入时间最新的\n"
        "     %USERPROFILE%\\AppData\\LocalLow\\VRChat\\VRChat\\output_log*.txt\n"
        "  2) 都没有时，退回 exe 同目录 / 当前目录 / exe 上级目录 中最新的\n"
        "     output_log*.txt\n"
        "\n"
        "界面操作：拖动移动；顶部按钮切换置顶/缩放/透明度/鼠标穿透/日志；\n"
        "底部箭头翻看历史局与历史 Boss 战；右键切换日志过滤；\n"
        "Ctrl+Alt+T 鼠标穿透，Ctrl+Alt+Q 退出。\n";
    MessageBoxA(NULL, msg, "Ecliptica HUD - 帮助", MB_OK | MB_ICONINFORMATION);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShow)
{
    (void)hInst; (void)hPrev; (void)lpCmdLine; (void)nShow;

    Config cfg;
    cfg_default(&cfg);

    bool demo = false;
    bool from_start = false;
    bool bad_arg = false;
    wchar_t logpath[MAX_PATH];
    logpath[0] = 0;

    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv) {
        for (int i = 1; i < argc; i++) {
            if (arg_is(argv[i], L"demo")) {
                demo = true;
            } else if (arg_is(argv[i], L"log")) {
                if (i + 1 < argc) {
                    wcsncpy(logpath, argv[++i], MAX_PATH - 1);
                    logpath[MAX_PATH - 1] = 0;
                    from_start = true;          /* 回放文件时从头解析 */
                } else {
                    bad_arg = true;             /* --log 后面没跟路径 */
                }
            } else if (arg_is(argv[i], L"tail")) {
                from_start = false;
            } else if (arg_is(argv[i], L"from-start")) {
                from_start = true;
            } else if (arg_is(argv[i], L"help") || arg_is(argv[i], L"h") ||
                       !wcscmp(argv[i], L"/?")) {
                LocalFree(argv);
                show_help();
                return 0;
            } else if (argv[i][0] == L'-') {
                bad_arg = true;                 /* 不认识的参数：别静默吞掉 */
            }
        }
        LocalFree(argv);
    }
    if (bad_arg) {
        show_help();                            /* 参数写错时直接告诉用户 */
        return 0;
    }

    wchar_t ini[MAX_PATH];
    cfg_path_w(ini, MAX_PATH);
    cfg_load(&cfg, ini);

    /* 注册 Ecliptica 系世界名（内置 "ecliptica" + 配置里的 world_names）*/
    names_set_world_aliases(cfg.world_names);

    if (logpath[0] && !demo) overlay_use_log(logpath);

    overlay_run(&cfg, demo, from_start);

    cfg_save(&cfg, ini);
    return 0;
}
