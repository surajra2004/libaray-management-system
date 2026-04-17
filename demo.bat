@echo off
echo Building...
g++ main.cpp -o libsys.exe
if %errorlevel% == 0 (
echo Running C++ Library System...
libsys.exe
) else (
echo Install g++ / MinGW first!
)
pause

