@echo off
REM Скрипт для быстрого тестирования передачи файла

echo ========================================
echo File Transfer Test Script
echo ========================================
echo.

echo Step 1: Building project...
cmake -S . -B cmake-build-debug -G "Ninja"
cmake --build cmake-build-debug --config Debug

echo.
echo Step 2: Creating test file...
echo Hello from test script! > test_file.txt
echo This is line 2 >> test_file.txt
echo This is line 3 >> test_file.txt

echo.
echo ========================================
echo Ready to test!
echo ========================================
echo.
echo Open TWO terminal windows and run:
echo.
echo Terminal 1 (Receiver):
echo    cd cmake-build-debug
echo    .\receiver.exe 8080 received.txt
echo.
echo Terminal 2 (Sender):
echo    cd cmake-build-debug
echo    .\sender.exe 127.0.0.1 8080 ..\test_file.txt
echo.
echo ========================================
pause

