/* preview.c - 离屏渲染界面预览（开发工具，不需要显示器 / VRChat）
 *
 *   preview.exe [日志文件] [缩放%] [日志面板0/1] [输出文件] [只回放前N行]
 *
 * 会把日志回放成真实统计状态，再渲染成 BMP，用于检查排版是否重叠、
 * 对齐是否正确、缩放是否一致。默认读取工作目录里的 output_log*.txt。
 */
#include "src/hud.h"
#include "src/stats.h"
#include "src/evlog.h"
#include "src/evtext.h"
#include "src/parse.h"
#include "src/zhtext.h"
#include "src/format.h"
#include "src/names.h"
#include "src/compat.h"
#include "src/names.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_bmp(const char* path, int w, int h, const void* bits)
{
    FILE* f = fopen(path, "wb");
    if (!f) { printf("cannot write %s\n", path); return; }
    int stride = w * 4;
    int size = stride * h;
    BITMAPFILEHEADER fh;
    BITMAPINFOHEADER ih;
    memset(&fh, 0, sizeof(fh));
    memset(&ih, 0, sizeof(ih));
    fh.bfType = 0x4D42;
    fh.bfOffBits = sizeof(fh) + sizeof(ih);
    fh.bfSize = fh.bfOffBits + size;
    ih.biSize = sizeof(ih);
    ih.biWidth = w;
    ih.biHeight = -h;
    ih.biPlanes = 1;
    ih.biBitCount = 32;
    ih.biCompression = BI_RGB;
    ih.biSizeImage = size;
    fwrite(&fh, sizeof(fh), 1, f);
    fwrite(&ih, sizeof(ih), 1, f);
    fwrite(bits, 1, (size_t)size, f);
    fclose(f);
    printf("wrote %s (%dx%d)\n", path, w, h);
}

static void replay(const char* path, Stats* st, EvLog* ev, long maxlines)
{
    FILE* f = fopen(path, "rb");
    if (!f) { printf("cannot open %s\n", path); return; }
    char line[2048];
    long n = 0, hits = 0;
    while (fgets(line, sizeof(line), f)) {
        size_t l = strlen(line);
        while (l > 0 && (line[l - 1] == '\n' || line[l - 1] == '\r')) line[--l] = 0;
        n++;
        Event e;
        if (parse_line(line, &e)) {
            if (stats_on_event(st, &e)) evtext_push(ev, st, &e);
            hits++;
        }
        if (maxlines > 0 && n >= maxlines) break;
    }
    fclose(f);
    printf("replayed %ld lines, %ld events from %s\n", n, hits, path);
}

static void seed_log(EvLog* ev, Stats* st)
{
    Event e;
    memset(&e, 0, sizeof(e));
    e.t = 0; e.type = EV_ROOM_ENTER; strcpy(e.name, "Ecliptica - Demo Playtest");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 1; e.type = EV_STAGE; strcpy(e.name, "ProtoColony"); strcpy(e.cls, "Nekomancer");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 2; e.type = EV_BOSS_FIGHT; strcpy(e.name, "FlyLord"); e.progress = 0.06;
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 3; e.type = EV_DEALT; e.amount = 1204;
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 4; e.type = EV_DAMAGE_TAKEN; e.amount = 43; strcpy(e.name, "(Peltapod) attack_Slam");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 5; e.type = EV_OWNERSHIP; strcpy(e.name, "FlyLord"); strcpy(e.cls, "OtherPlayer");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 6; e.type = EV_TOKEN_SPAWN;
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 7; e.type = EV_DAMAGE_TAKEN; e.amount = 118; strcpy(e.name, "attack_Spit (2)");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 8; e.type = EV_PLAYER_DEAD;
    stats_on_event(st, &e); evtext_push(ev, st, &e);
    e.t = 9; e.type = EV_BOSS_DEAD; strcpy(e.name, "FlyLord");
    stats_on_event(st, &e); evtext_push(ev, st, &e);
}

int main(int argc, char** argv)
{
    const char* logpath = argc > 1 ? argv[1] : NULL;
    int scale = argc > 2 ? atoi(argv[2]) : 100;
    int withlog = argc > 3 ? atoi(argv[3]) : 1;
    const char* out = argc > 4 ? argv[4] : "hud_preview.bmp";
    long maxlines = argc > 5 ? atol(argv[5]) : 0;
    if (scale < 50) scale = 50;
    if (scale > 300) scale = 300;

    Stats st;
    EvLog ev;
    stats_init(&st);
    evlog_init(&ev);
    if (logpath && strcmp(logpath, "-") != 0) replay(logpath, &st, &ev, maxlines);
    else seed_log(&ev, &st);

    Config cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.always_on_top = true;
    cfg.alpha = 255;
    cfg.scale = scale;
    cfg.stat_window = 10;
    cfg.show_event_log = withlog != 0;
    cfg.ev_filter = EVFILT_ALL;

    int w = HUD_BASE_W * scale / 100;
    int h = HUD_BASE_H * scale / 100;

    HDC scr = GetDC(NULL);
    HDC dc = CreateCompatibleDC(scr);
    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = NULL;
    HBITMAP bmp = CreateDIBSection(scr, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
    ReleaseDC(NULL, scr);
    if (!bmp) { printf("CreateDIBSection failed\n"); return 1; }
    SelectObject(dc, bmp);

    SetMapMode(dc, MM_ANISOTROPIC);
    SetWindowExtEx(dc, HUD_BASE_W, HUD_BASE_H, NULL);
    SetViewportExtEx(dc, w, h, NULL);

    HudLayout L;
    hud_layout(HUD_BASE_W, HUD_BASE_H, withlog != 0, &L);

    StatsView view;
    stats_view(&st, st.last_t, (double)cfg.stat_window, &view);

    char status[192];
    if (st.in_fight)
        snprintf_(status, sizeof(status), "%s · %s", TXT_RUNNING,
                  st.cur_fight.disp[0] ? st.cur_fight.disp : "Boss");
    else if (st.in_world) snprintf_(status, sizeof(status), "%s", TXT_IDLE_WORLD);
    else snprintf_(status, sizeof(status), "%s", TXT_WAIT_JOIN);

    hud_paint(dc, &L, &cfg, &view, &ev, status, "output_log.txt", HUD_BTN_LOG, 0);

    write_bmp(out, w, h, bits);

    DeleteObject(bmp);
    DeleteDC(dc);
    hud_free_fonts();
    return 0;
}
