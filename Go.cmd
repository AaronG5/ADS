@echo off
REM Check if gcc is installed
where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo gcc is not installed. Please install gcc to compile the program.
    exit /b 1
)

REM Compile the C program
gcc -o program.exe main.c
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b 1
)

REM Run the compiled program
program.exe