/* uitext.h - 界面文案派发（按编译期选定的语言包含对应文案表）
 *
 *   mingw32-make            -> 中文（默认）hr-dlc.exe
 *   mingw32-make LANG=en    -> English      hr-dlc-en.exe
 *   mingw32-make LANG=ja    -> 日本語        hr-dlc-ja.exe
 *
 * 新增文案时必须三个 uitext_*.h 一起补，否则对应语言的编译会报未定义。 */
#ifndef UITEXT_H
#define UITEXT_H

#if defined(UI_LANG_EN)
#include "uitext_en.h"
#elif defined(UI_LANG_JA)
#include "uitext_ja.h"
#else
#include "uitext_zh.h"
#endif

#endif
