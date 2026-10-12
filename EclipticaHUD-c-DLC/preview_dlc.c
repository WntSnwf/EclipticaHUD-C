/* preview_dlc.c - 离屏渲染 DLC 面板，输出 BMP
 *
 * 用来在没有显示器（或不想弹窗）的环境下检查排版：
 *   preview_dlc.exe <表文件> <内部名> <形态号> <缩放%> <输出.bmp>
 * 例：
 *   preview_dlc.exe "Weakness&Resistance.txt" FlyLord 1 100 out.bmp
 * 内部名传 "-" 或不传：渲染"等待 Boss 战"状态。
 * 内部名传一个表里没有的名字：渲染"数据表里没有这只 Boss"状态。
 */
#include "dlcui.h"
#include "res.h"
#include "uitext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_bmp(const char* path, int w, int h, const void* bits)
{
    FILE* f = fopen(path, "wb");
    if (!f) { printf("cannot write %s\n", path); return; }
    int size = w * h * 4;
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

int main(int argc, char** argv)
{
    const char* tbl = argc > 1 ? argv[1] : "Weakness&Resistance.txt";
    const char* boss = argc > 2 ? argv[2] : NULL;
    if (boss && !strcmp(boss, "-")) boss = NULL;      /* "-" = 没有 Boss 战 */
    int phase = argc > 3 ? atoi(argv[3]) : 1;
    int scale = argc > 4 ? atoi(argv[4]) : 100;
    const char* out = argc > 5 ? argv[5] : "dlc_preview.bmp";
    if (scale < 50) scale = 50;
    if (scale > 300) scale = 300;

    static ResTable T;
    bool ok = res_load(&T, tbl);
    if (!ok) printf("warning: cannot open %s, rendering as 'no data'\n", tbl);

    DlcLayout L;
    dlcui_layout(&L);

    int w = DLC_W * scale / 100;
    int h = DLC_H * scale / 100;

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

    DlcView v;
    memset(&v, 0, sizeof(v));
    char disp[96];
    disp[0] = 0;
    v.boss_display = disp;
    v.status = TXT_ST_WAITING;
    /* 与运行时一致：只显示时间戳部分（运行时会把 output_log_ 前缀和 .txt 去掉）*/
    v.logname = "2026-10-12_19-00-00";

    if (boss && boss[0]) {
        /* 与运行时一致：先用基础名（去掉 (Clone)/PhaseN），形态号另外给。
         * 不传形态号时从名字里推。 */
        char base[64];
        int ph = res_boss_phase(boss);
        res_boss_base(boss, base, sizeof(base));
        if (argc > 3) ph = phase;
        snprintf(disp, sizeof(disp), "%s", res_boss_display(base));
        v.in_fight = true;
        v.phase = ph;
        v.res = ok ? res_find(&T, base, ph) : NULL;
        v.status = v.res ? TXT_ST_LOCKED : TXT_NO_DATA;
    }

    SetMapMode(dc, MM_ANISOTROPIC);
    SetWindowExtEx(dc, DLC_W, DLC_H, NULL);
    SetViewportExtEx(dc, w, h, NULL);
    dlcui_paint(dc, &L, &v, 0, 0.0);
    SetMapMode(dc, MM_TEXT);

    write_bmp(out, w, h, bits);

    DeleteObject(bmp);
    DeleteDC(dc);
    dlcui_free_fonts();
    return 0;
}
