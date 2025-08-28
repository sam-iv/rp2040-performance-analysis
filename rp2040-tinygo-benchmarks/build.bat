@echo off
setlocal ENABLEEXTENSIONS
cls

echo ============================================
echo        TinyGo RP2040 Benchmarker
echo ============================================
echo Available Benchmarks:
echo   1. fibonacci
echo   2. bubble
echo   3. quick
echo   4. loop
echo   5. matrix
echo   6. fft
echo   7. adc
echo   8. gpio
echo   9. uart
echo  10. interrupt
echo  11. pwm
echo  12. i2c
echo.

set /p benchChoice="Enter number of benchmark to build: "

set "src="
if "%benchChoice%"=="1" set src=fibonacci
if "%benchChoice%"=="2" set src=bubble
if "%benchChoice%"=="3" set src=quick
if "%benchChoice%"=="4" set src=loop
if "%benchChoice%"=="5" set src=matrix
if "%benchChoice%"=="6" set src=fft
if "%benchChoice%"=="7" set src=adc
if "%benchChoice%"=="8" set src=gpio
if "%benchChoice%"=="9" set src=uart
if "%benchChoice%"=="10" set src=interrupt
if "%benchChoice%"=="11" set src=pwm
if "%benchChoice%"=="12" set src=i2c

if not defined src (
    echo Invalid choice. Exiting.
    exit /b
)

echo.
echo Building TinyGo benchmark: %src%
echo ----------------------------

mkdir build 2>nul
tinygo build -target pico -o build\%src%.uf2 .\src\%src%

if exist build\%src%.uf2 (
    echo Build successful! File saved to build\%src%.uf2
) else (
    echo Build failed. Please check for errors.
)

pause
