# Ecliptica HUD DLC - Boss 弱点 / 抗性面板
#
#   mingw32-make                中文版 -> hr-dlc.exe
#   mingw32-make LANG=en        英文版 -> hr-dlc-en.exe
#   mingw32-make LANG=ja        日文版 -> hr-dlc-ja.exe
#   mingw32-make test           构建并运行逻辑测试（控制台）
#   mingw32-make preview        离屏渲染面板预览图（无需显示器）
#   mingw32-make run-demo       跑起来看轮播演示
#   mingw32-make clean
#
# 三种语言共用同一份源码，只有 uitext_*.h 不同，由 LANG 决定包含哪个。
# 中间文件按语言分目录（build/<lang>/），切换语言不会串用旧的目标文件。
#
# MSVC 用户可直接运行 build.bat（同样支持 build.bat en / build.bat ja）。

CC := gcc

# ---- 语言选择 ----
LANG ?= zh

ifeq ($(LANG),zh)
  LANGDEF =
  SUF     =
else ifeq ($(LANG),en)
  LANGDEF = -DUI_LANG_EN
  SUF     = -en
else ifeq ($(LANG),ja)
  LANGDEF = -DUI_LANG_JA
  SUF     = -ja
else
  $(error LANG 只能是 zh / en / ja，当前是 "$(LANG)")
endif

CFLAGS  ?= -O2 -Wall -Wextra -std=gnu11 -DUNICODE -D_UNICODE \
           -finput-charset=UTF-8 -fexec-charset=UTF-8
CFLAGS  += $(LANGDEF)
LDFLAGS ?= -mwindows
LIBS     = -lgdi32 -luser32

SRCS = dlc.c dlcui.c logtail.c res.c
OBJDIR = build/$(LANG)
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
# 头文件也作为依赖：改了 uitext_*.h 里的文案必须触发重编
HDRS = $(wildcard *.h)

TARGET  = hr-dlc$(SUF).exe
TESTBIN = test_dlc$(SUF).exe
PREVBIN = preview_dlc$(SUF).exe

TEST_SRCS = test_dlc.c res.c logtail.c
PREV_SRCS = preview_dlc.c dlcui.c res.c

ifeq ($(OS),Windows_NT)
  RUN   =
  CLEAN = del /q
  MKDIR = -mkdir
  RMDIR = -rmdir /s /q
else
  RUN   = ./
  CLEAN = rm -f
  MKDIR = -mkdir -p
  RMDIR = -rm -rf
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.c $(HDRS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(MKDIR) $(subst /,\,$(OBJDIR))

$(TESTBIN): $(TEST_SRCS) $(HDRS)
	$(CC) -O2 -Wall -Wextra -std=gnu11 $(LANGDEF) \
	      -finput-charset=UTF-8 -fexec-charset=UTF-8 -o $@ $(TEST_SRCS)

$(PREVBIN): $(PREV_SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(PREV_SRCS) -lgdi32 -luser32

test: $(TESTBIN)
	$(RUN)$(TESTBIN)

preview: $(PREVBIN)
	$(RUN)$(PREVBIN)

run-demo: $(TARGET)
	$(RUN)$(TARGET) --demo

clean:
	-$(CLEAN) $(subst /,\,$(OBJS)) 2>nul
	-$(CLEAN) hr-dlc.exe hr-dlc-en.exe hr-dlc-ja.exe 2>nul
	-$(CLEAN) test_dlc.exe test_dlc-en.exe test_dlc-ja.exe 2>nul
	-$(CLEAN) preview_dlc.exe preview_dlc-en.exe preview_dlc-ja.exe 2>nul
	-$(RMDIR) build 2>nul

.PHONY: all clean test preview run-demo
