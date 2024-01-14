@REM good tuto: https://www.tutorialspoint.com/batch_script

@echo OFF
@REM echo %0
@REM echo %~dp0
cd /d %~dp0
cd lib
echo compiling lib files ...
gcc *.c -c -Wall -Wextra
if %ERRORLEVEL% gtr 0 (
    echo compilation failed
    pause
    exit /b 1
)
cd ..\src
echo compiling src files ...
gcc *.c -c -Wall -Wextra
if %ERRORLEVEL% gtr 0 (
    echo compilation failed
    pause
    exit /b 1
)
cd ..
echo compiling rogue_like.exe ...
gcc .\lib\*.o .\src\*.o -o .\rogue_like.exe -Wall -Wextra
if %ERRORLEVEL% gtr 0 (
    echo compilation failed
    pause
    exit /b 1
)
echo compilation successful
pause
exit /b 0
