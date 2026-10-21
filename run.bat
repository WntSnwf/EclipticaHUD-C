@echo off
rem ===========================================================================
rem  Ecliptica HUD - launcher
rem  Starts the main HUD and the companion DLC (weakness / resistance panel).
rem ---------------------------------------------------------------------------
rem  Usage:
rem    run.bat                 start the Chinese builds        (default)
rem    run.bat en              start the English builds
rem    run.bat ja              start the Japanese builds
rem    run.bat --demo          extra arguments are passed to BOTH programs
rem    run.bat en --demo       (e.g. demo mode needs no VRChat running)
rem    run.bat /n              dry run - print what would be started, start nothing
rem
rem  Both programs are launched without waiting, then this script exits.
rem  A missing main HUD is an error; a missing DLC is only a warning.
rem
rem  NOTE - why this file is pure ASCII:
rem    cmd.exe decodes .bat files using the OEM code page. On a cp936
rem    (Chinese) console a UTF-8 .bat is mis-read, and the mangled pieces
rem    are then executed as commands instead of being echoed. Verified, so
rem    all text here is ASCII on purpose. The Chinese/Japanese docs explain
rem    the same thing in prose.
rem ===========================================================================

setlocal
rem Capture the script folder FIRST. "shift" also shifts %0, so %~dp0 would
rem afterwards resolve to the first argument instead of this script.
set "HERE=%~dp0"

set "LANG="
set "DRY="
set "EXTRA="

:parse
if "%~1"=="" goto parsed
set "ARG=%~1"
if /i "%ARG%"=="zh"    (set "LANG=zh" & shift & goto parse)
if /i "%ARG%"=="en"    (set "LANG=en" & shift & goto parse)
if /i "%ARG%"=="ja"    (set "LANG=ja" & shift & goto parse)
if /i "%ARG%"=="/n"    (set "DRY=1"   & shift & goto parse)
if /i "%ARG%"=="-n"    (set "DRY=1"   & shift & goto parse)
if /i "%ARG%"=="--dry" (set "DRY=1"   & shift & goto parse)
set "EXTRA=%EXTRA% %ARG%"
shift
goto parse

:parsed
if not defined LANG set "LANG=zh"
if /i "%LANG%"=="zh" (set "SUF=") else (set "SUF=-%LANG%")

rem ---- locate the two executables -------------------------------------------
rem  Both are searched next to this script and one level up, so the same
rem  launcher works for the repository layout (DLC in a subfolder), for the
rem  local layout (DLC as a sibling folder) and for a flat download where
rem  every exe sits in one folder.

set "MAIN="
if exist "%HERE%ecliptica-hud-c%SUF%.exe" set "MAIN=%HERE%ecliptica-hud-c%SUF%.exe"
if not defined MAIN if exist "%HERE%..\ecliptica-hud-c%SUF%.exe" set "MAIN=%HERE%..\ecliptica-hud-c%SUF%.exe"

set "DLC="
for %%D in ("%HERE%EclipticaHUD-c-DLC" "%HERE%..\EclipticaHUD-c-DLC" "%HERE%dlc" "%HERE%" "%HERE%..") do (
    if not defined DLC call :try_dlc "%%~fD"
)

rem ---- report / launch -------------------------------------------------------

if not defined MAIN (
    echo.
    echo [ERROR] Main HUD not found: ecliptica-hud-c%SUF%.exe
    echo.
    echo   looked in:
    echo     %HERE%
    echo     %HERE%..
    echo.
    echo   Put the main HUD exe next to this script, or build it first
    echo   ^(mingw32-make / build.bat^). See README.md.
    echo.
    pause
    exit /b 1
)

if not defined DLC (
    echo.
    echo [WARN] DLC not found: hr-dlc%SUF%.exe  -- starting the main HUD only.
    echo.
    echo   looked in:
    echo     %HERE%EclipticaHUD-c-DLC\
    echo     %HERE%..\EclipticaHUD-c-DLC\
    echo     %HERE%
    echo.
    echo   See EclipticaHUD-c-DLC\README.md.
    echo.
)

echo Language : %LANG%
echo Main HUD : %MAIN%
if defined DLC echo DLC      : %DLC%
if defined EXTRA echo Args     :%EXTRA%
echo.

if defined DRY (
    echo [dry run] nothing was started.
    exit /b 0
)

rem The programs resolve their own config/data files from their exe path,
rem so the working directory only has to be somewhere sane.
pushd "%HERE%"
start "" "%MAIN%" %EXTRA%
if defined DLC start "" "%DLC%" %EXTRA%
popd

exit /b 0

rem ---- helpers ---------------------------------------------------------------
rem  %1 = a candidate folder. Sets DLC if hr-dlc<SUF>.exe lives in it.
rem  Trailing backslashes are trimmed so the reported path has no "\\" in it.
:try_dlc
if defined DLC goto :eof
set "CAND=%~1"
if "%CAND:~-1%"=="\" set "CAND=%CAND:~0,-1%"
if exist "%CAND%\hr-dlc%SUF%.exe" set "DLC=%CAND%\hr-dlc%SUF%.exe"
goto :eof
