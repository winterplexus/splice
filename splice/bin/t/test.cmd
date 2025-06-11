@echo off

echo.splice 1.3.0 release 1
echo.splice test script - Microsoft Windows OS environment
echo.================================================================================

if not exist "destination" mkdir destination

echo.
echo.test case 01: splice 2 source binary files into 1 destination binary file
echo.--------------------------------------------------------------------------------
echo.

splice.exe -i source -b test-1.dat -o destination\output-1.dat -s -v

echo.
move destination\output-1.dat destination\output.zip
cd destination
unzip output.zip
rd /s test /q
cd ..
del destination\* /q
echo.

echo.test case 02: splice 2 source binary files into 1 destination binary file
echo.--------------------------------------------------------------------------------
echo.

splice.exe -i source -b test-2.dat -o destination\output-2.dat -s -v

echo.
dir destination
del destination\* /q
echo.
