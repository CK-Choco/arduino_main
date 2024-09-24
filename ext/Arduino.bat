@echo off
chcp 950
CLS
:menu
CLS
echo =====================
echo 1. 備份 Arduino 開發板 / 程式庫
echo 2. 覆蓋 Arduino 開發板 / 程式庫
echo 3. 退出
echo =====================
choice /c 123 /n /m "請選擇一個選項: "

if errorlevel 3 (
    exit
) else if errorlevel 2 (
    xcopy /e /Y "%~d0\Documents\Arduino" "C:\Users\%username%\Documents\Arduino" 
    goto menu
) else if errorlevel 1 (
    xcopy /e /Y "C:\Users\%username%\Documents\Arduino" "%~d0\Documents\Arduino"
    goto menu
)
