@echo off
REM DSA Setup for Windows
REM This script installs WSL2 with Ubuntu, which is required to run the DSA project.
REM After WSL is installed, run ./setup.sh inside WSL to install the C++ toolchain.

echo.
echo  DSA Setup - Windows
echo  ====================
echo.

REM Check if WSL is already installed
wsl --status >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo  WSL is already installed.
    echo.

    REM Check if Ubuntu is available
    wsl -l -q 2>nul | findstr /i "Ubuntu" >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        echo  Ubuntu is available. Launching setup inside WSL...
        echo.
        wsl -d Ubuntu -- bash -c "cd \"$(wslpath '%~dp0')\" && ./setup.sh"
        goto :done
    ) else (
        echo  Ubuntu not found. Installing Ubuntu...
        echo.
        wsl --install -d Ubuntu
        echo.
        echo  Ubuntu has been installed.
        echo  Please restart your PC, then run this script again.
        goto :done
    )
) else (
    echo  WSL is not installed. Installing WSL2 with Ubuntu...
    echo  (This requires Administrator privileges)
    echo.
    wsl --install -d Ubuntu
    echo.
    echo  ==========================================================
    echo   WSL2 with Ubuntu has been installed.
    echo.
    echo   NEXT STEPS:
    echo     1. Restart your PC
    echo     2. Open Ubuntu from the Start menu
    echo     3. Set up your Unix username and password when prompted
    echo     4. Navigate to this project folder and run:
    echo.
    echo        cd /mnt/c/path/to/DSA
    echo        ./setup.sh
    echo.
    echo   Or just double-click setup.bat again after restarting.
    echo  ==========================================================
)

:done
echo.
pause
