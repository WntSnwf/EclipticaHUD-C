@echo off
rem Ecliptica HUD DLC - MSVC build script
rem
rem   build.bat            中文版 -> hr-dlc.exe
rem   build.bat en         English -> hr-dlc-en.exe
rem   build.bat ja         日本語   -> hr-dlc-ja.exe
rem
rem Run inside "x64 Native Tools Command Prompt for VS 2022", in this folder.
rem Requires VS2015 or newer (/utf-8 and C99 snprintf).

setlocal
set "LANG=%~1"
if "%LANG%"=="" set "LANG=zh"

if /i "%LANG%"=="zh" (set "LANGDEF=" & set "SUF=")
if /i "%LANG%"=="en" (set "LANGDEF=/DUI_LANG_EN" & set "SUF=-en")
if /i "%LANG%"=="ja" (set "LANGDEF=/DUI_LANG_JA" & set "SUF=-ja")
if not defined SUF if /i not "%LANG%"=="zh" goto :badlang

set "SRC=dlc.c dlcui.c logtail.c res.c tablepath.c"

echo [1/2] Building hr-dlc%SUF%.exe (LANG=%LANG%) ...
cl /nologo /O2 /W3 /std:c11 /DUNICODE /D_UNICODE /utf-8 %LANGDEF% ^
   %SRC% ^
   /link /SUBSYSTEM:WINDOWS user32.lib gdi32.lib ^
   /OUT:hr-dlc%SUF%.exe
if errorlevel 1 goto :fail

echo [2/2] Building logic tests test_dlc%SUF%.exe ...
cl /nologo /O2 /W3 /std:c11 /utf-8 %LANGDEF% ^
   test_dlc.c res.c logtail.c tablepath.c ^
   /Fe:test_dlc%SUF%.exe
if errorlevel 1 goto :fail

del /q *.obj >nul 2>nul
echo.
echo Done: hr-dlc%SUF%.exe / test_dlc%SUF%.exe
echo Run .\test_dlc%SUF%.exe to execute the 143 logic checks.
exit /b 0

:badlang
echo.
echo Unknown language "%LANG%". Use: build.bat [zh^|en^|ja]
exit /b 1

:fail
echo.
echo Build failed.
exit /b 1
