/* zhtext.h - 界面文案派发（按编译期选定的语言包含对应文案表）
 *
 * 三种语言共用同一组宏名，源码里一律写宏，不写死字符串。
 * 构建方式见 Makefile：
 *   mingw32-make            -> 中文（默认）
 *   mingw32-make LANG=en    -> 英文
 *   mingw32-make LANG=ja    -> 日文
 *
 * 新增文案时必须三个 zhtext_*.h 一起补，否则对应语言的编译会报未定义。 */
#ifndef ZHTEXT_H
#define ZHTEXT_H

#if defined(UI_LANG_EN)
#include "zhtext_en.h"
#elif defined(UI_LANG_JA)
#include "zhtext_ja.h"
#else
#include "zhtext_zh.h"
#endif

#endif
