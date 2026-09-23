/* main.c - Ecliptica HUD (C) 入口
 *
 * 用法：
 *   ecliptica-hud-c.exe                  跟随 VRChat 实时日志
 *   ecliptica-hud-c.exe --demo           演示模式（内置真实格式的模拟日志）
 *   ecliptica-hud-c.exe --log 文件       回放指定日志（从头解析，并继续跟随新增行）
 *   ecliptica-hud-c.exe --tail           自动定位日志时也从头解析（默认跳到末尾）
 *   ecliptica-hud-c.exe --help           显示本帮助
 */
#include "cfg.h"
#include "names.h"
#include "overlay.h"
#include "compat.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

static void show_help(void)
{
    const char* msg =
        "Ecliptica HUD (C)\n"
        "\n"
        "  ecliptica-hud-c.exe              跟随 VRChat 实时日志\n"
        "  ecliptica-hud-c.exe --demo       演示模式（无需 VRChat）\n"
        "  ecliptica-hud-c.exe --log FILE   回放指定日志文件，并继续跟随新增内容\n"
        "  ecliptica-hud-c.exe --tail       自动定位日志时也从头解析\n"
        "  ecliptica-hud-c.exe --help       显示帮助\n"
        "\n"
        "日志自动定位顺序：\n"
        "  1) %USERPROFILE%\\AppData\\LocalLow\\VRChat\\VRChat\\output_log.txt\n"
        "  2) exe 同目录 / 当前目录 / exe 上级目录 中最新的 output_log*.txt\n"
        "\n"
        "界面操作：拖动移动；顶部按钮切换置顶/缩放/透明度/统计窗口/日志；\n"
        "底部箭头翻看历史局与历史 Boss 战；右键切换日志过滤；Ctrl+Alt+Q 退出。\n";
    MessageBoxA(NULL, msg, "Ecliptica HUD - 帮助", MB_OK | MB_ICONINFORMATION);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShow)
{
    (void)hInst; (void)hPrev; (void)lpCmdLine; (void)nShow;

    Config cfg;
    cfg_default(&cfg);

    bool demo = false;
    bool from_start = false;
    wchar_t logpath[MAX_PATH];
    logpath[0] = 0;

    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv) {
        for (int i = 1; i < argc; i++) {
            if (!wcscmp(argv[i], L"--demo")) {
                demo = true;
            } else if (!wcscmp(argv[i], L"--log") && i + 1 < argc) {
                wcsncpy(logpath, argv[++i], MAX_PATH - 1);
                logpath[MAX_PATH - 1] = 0;
                from_start = true;              /* 回放文件时从头解析 */
            } else if (!wcscmp(argv[i], L"--tail")) {
                from_start = false;
            } else if (!wcscmp(argv[i], L"--from-start")) {
                from_start = true;
            } else if (!wcscmp(argv[i], L"--help") || !wcscmp(argv[i], L"-h") ||
                       !wcscmp(argv[i], L"/?")) {
                LocalFree(argv);
                show_help();
                return 0;
            }
        }
        LocalFree(argv);
    }

    wchar_t ini[MAX_PATH];
    cfg_path_w(ini, MAX_PATH);
    cfg_load(&cfg, ini);

    /* 注册 Ecliptica 系世界名（内置 "ecliptica" / "男生女生向前冲" + 配置追加）*/
    names_set_world_aliases(cfg.world_names);

    if (logpath[0] && !demo) overlay_use_log(logpath);

    overlay_run(&cfg, demo, from_start);

    cfg_save(&cfg, ini);
    return 0;
}
