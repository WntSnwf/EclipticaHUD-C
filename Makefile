# Ecliptica HUD (C) - Windows (MinGW-w64) 构建
#
#   mingw32-make                本机 gcc 构建（中文版）
#   mingw32-make LANG=en        英文版  -> ecliptica-hud-c-en.exe
#   mingw32-make LANG=ja        日文版  -> ecliptica-hud-c-ja.exe
#   mingw32-make CC=x86_64-w64-mingw32-gcc     Linux 交叉编译
#   mingw32-make test           构建并运行逻辑测试（控制台程序）
#   mingw32-make preview        离屏渲染界面预览图 hud_preview.bmp
#   mingw32-make clean
#
# 三种语言共用同一份源码，只有 src/zhtext_*.h 不同，由 LANG 决定包含哪个。
# 中间文件按语言分目录存放（build/<lang>/），切换语言不会串用旧的目标文件。

# 注意用 := 而不是 ?=：make 内置 CC=cc，?= 不会生效
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

SRCS = src/main.c src/overlay.c src/hud.c src/vlog.c src/parse.c \
       src/stats.c src/evlog.c src/cfg.c src/format.c src/names.c src/evtext.c

# 头文件也作为依赖：否则改了 src/zhtext_*.h 里的文案/宽度不会触发重编，
# 会拿旧目标文件链接出"看起来没生效"的 exe。
HDRS = $(wildcard src/*.h)

OBJDIR = build/$(LANG)
OBJS   = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

TARGET  = ecliptica-hud-c$(SUF).exe
TESTBIN = test_core$(SUF).exe
PREVBIN = preview$(SUF).exe

# 逻辑测试（控制台，覆盖解析 + 统计 + 名称 + 格式化 + 事件日志）
TEST_SRCS = test_core.c src/parse.c src/stats.c src/evlog.c src/format.c \
            src/names.c src/evtext.c

# 界面预览（离屏渲染成 BMP，无需显示器即可检查排版）
PREVIEW_SRCS = preview.c src/hud.c src/format.c src/names.c src/parse.c \
               src/stats.c src/evlog.c src/evtext.c

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

$(OBJDIR)/%.o: src/%.c $(HDRS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(MKDIR) $(subst /,\,$(OBJDIR))

$(TESTBIN): $(TEST_SRCS) $(HDRS)
	$(CC) -O2 -Wall -Wextra -std=gnu11 $(LANGDEF) \
	      -finput-charset=UTF-8 -fexec-charset=UTF-8 -o $@ $(TEST_SRCS)

$(PREVBIN): $(PREVIEW_SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(PREVIEW_SRCS) -lgdi32 -luser32

test: $(TESTBIN)
	$(RUN)$(TESTBIN)

preview: $(PREVBIN)
	$(RUN)$(PREVBIN)

clean:
	-$(CLEAN) $(subst /,\,$(OBJS)) ecliptica-hud-c.exe ecliptica-hud-c-en.exe ecliptica-hud-c-ja.exe 2>nul
	-$(CLEAN) test_core.exe test_core-en.exe test_core-ja.exe 2>nul
	-$(CLEAN) preview.exe preview-en.exe preview-ja.exe 2>nul
	-$(RMDIR) build 2>nul

.PHONY: all clean test preview
