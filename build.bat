@echo off
rem Ecliptica HUD (C) - MSVC 构建脚本
rem 在 "x64 Native Tools Command Prompt for VS 2022" 中，于本目录下运行。
rem 需要 VS2015 或更新版本（/utf-8 与 C99 snprintf）。

setlocal
set SRC=src\main.c src\overlay.c src\hud.c src\vlog.c src\parse.c ^
        src\stats.c src\evlog.c src\cfg.c src\format.c src\names.c src\evtext.c

echo [1/2] 编译 ecliptica-hud-c.exe ...
cl /nologo /O2 /W3 /std:c11 /DUNICODE /D_UNICODE /utf-8 ^
   %SRC% ^
   /link /SUBSYSTEM:WINDOWS user32.lib gdi32.lib ^
   /OUT:ecliptica-hud-c.exe
if errorlevel 1 goto :fail

echo [2/2] 编译逻辑测试 test_core.exe ...
cl /nologo /O2 /W3 /std:c11 /utf-8 ^
   test_core.c src\parse.c src\stats.c src\evlog.c src\format.c src\names.c ^
   /Fe:test_core.exe
if errorlevel 1 goto :fail

del /q *.obj >nul 2>nul
echo.
echo 构建完成：ecliptica-hud-c.exe / test_core.exe
echo 运行 .\test_core.exe 可执行 107 项逻辑检查。
exit /b 0

:fail
echo.
echo 构建失败。
exit /b 1
