# Ecliptica HUD (C) - Windows (MinGW-w64) 构建
#
#   mingw32-make                本机 gcc 构建
#   mingw32-make CC=x86_64-w64-mingw32-gcc     Linux 交叉编译
#   mingw32-make test           构建并运行逻辑测试（控制台程序）
#   mingw32-make preview        离屏渲染界面预览图 hud_preview.bmp
#   mingw32-make clean

# 注意用 := 而不是 ?=：make 内置 CC=cc，?= 不会生效
CC := gcc

CFLAGS  ?= -O2 -Wall -Wextra -std=gnu11 -DUNICODE -D_UNICODE \
           -finput-charset=UTF-8 -fexec-charset=UTF-8
LDFLAGS ?= -mwindows
LIBS     = -lgdi32 -luser32

SRCS = src/main.c src/overlay.c src/hud.c src/vlog.c src/parse.c \
       src/stats.c src/evlog.c src/cfg.c src/format.c src/names.c src/evtext.c
OBJS = $(SRCS:.c=.o)

TARGET = ecliptica-hud-c.exe

# 逻辑测试（控制台，覆盖解析 + 统计 + 名称 + 格式化 + 事件日志）
TEST_SRCS = test_core.c src/parse.c src/stats.c src/evlog.c src/format.c \
            src/names.c src/evtext.c

# 界面预览（离屏渲染成 BMP，无需显示器即可检查排版）
PREVIEW_SRCS = preview.c src/hud.c src/format.c src/names.c src/parse.c \
               src/stats.c src/evlog.c src/evtext.c

ifeq ($(OS),Windows_NT)
  RUN   =
  CLEAN = del /q
else
  RUN   = ./
  CLEAN = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_core.exe: $(TEST_SRCS)
	$(CC) -O2 -Wall -Wextra -std=gnu11 -finput-charset=UTF-8 -fexec-charset=UTF-8 \
	      -o $@ $(TEST_SRCS)

preview.exe: $(PREVIEW_SRCS)
	$(CC) $(CFLAGS) -o $@ $(PREVIEW_SRCS) -lgdi32 -luser32

test: test_core.exe
	$(RUN)test_core.exe

preview: preview.exe
	$(RUN)preview.exe

clean:
	-$(CLEAN) $(subst /,\,$(OBJS)) $(TARGET) test_core.exe preview.exe *.o 2>nul

.PHONY: all clean test preview
