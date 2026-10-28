/* compat.h - 编译期兼容垫片 */
#ifndef COMPAT_H
#define COMPAT_H

#include <stdio.h>

/* MSVC 2015 之前没有 C99 snprintf / swprintf */
#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf_  _snprintf
#define vsnprintf_ _vsnprintf
#define snwprintf_ _snwprintf
#else
#define snprintf_  snprintf
#define vsnprintf_ vsnprintf
#define snwprintf_ swprintf
#endif

#endif
