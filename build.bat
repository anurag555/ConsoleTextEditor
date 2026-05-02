@echo off
setlocal
cd /d "%~dp0"
gcc src\main.c src\editor.c src\file.c -o editor.exe
if errorlevel 1 exit /b 1
echo Built editor.exe. Run: editor.exe test.txt
exit /b 0
