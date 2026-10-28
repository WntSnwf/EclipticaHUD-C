/* tablepath.h - 抗性表放在哪：按固定顺序查找
 *
 * 单独抽成一个模块，是为了能单元测试 —— "查找顺序"这种东西最容易在
 * 后续改动里悄悄改坏，而它坏了的表现只是"面板说找不到表"，很难查。
 *
 * 查找顺序（先找到先用）：
 *   1. --table 指定的文件        —— 指定了就只用它，不做任何回退
 *   2. <exe 目录>\Weakness&Resistance.txt        （标准摆放）
 *   3. <exe 目录>\EclipticaHUD-c-DLC\...         （exe 在仓库根目录）
 *   4. <exe 目录>\..\Weakness&Resistance.txt     （exe 在 bin\ 之类子目录）
 *   5. <exe 目录>\..\EclipticaHUD-c-DLC\...
 *   6. <当前工作目录>\Weakness&Resistance.txt    （从别处启动）
 *   7. <当前工作目录>\EclipticaHUD-c-DLC\...
 */
#ifndef TABLEPATH_H
#define TABLEPATH_H

#include <windows.h>
#include <stdbool.h>

#define TABLE_FILE_NAME  L"Weakness&Resistance.txt"
/* 仓库布局下 DLC 自己所在的子目录名 */
#define TABLE_SUBDIR     L"EclipticaHUD-c-DLC"

typedef struct {
    wchar_t path[MAX_PATH];   /* 找到的完整路径；空串 = 没找到 */
    wchar_t hint[MAX_PATH];   /* 建议放置的目录（= exe 同目录）*/
    bool    forced;           /* 来自 --table */
} TablePath;

/* exe_dir 为 NULL 时取自身 exe 所在目录；cwd 为 NULL 时取当前工作目录。
 * 测试可以显式传入，避免依赖真实目录布局。*/
void table_find(TablePath* tp, const wchar_t* forced,
                const wchar_t* exe_dir, const wchar_t* cwd);

#endif
