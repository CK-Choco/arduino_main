@echo off
chcp 950
CLS
:menu
CLS
echo =====================
echo 1. �ƥ� Arduino �}�o�O / �{���w
echo 2. �л\ Arduino �}�o�O / �{���w
echo 3. �h�X
echo =====================
choice /c 123 /n /m "�п�ܤ@�ӿﶵ: "

if errorlevel 3 (
    exit
) else if errorlevel 2 (
    xcopy /e /Y "%~d0\Documents\Arduino" "C:\Users\%username%\Documents\Arduino" 
    goto menu
) else if errorlevel 1 (
    xcopy /e /Y "C:\Users\%username%\Documents\Arduino" "%~d0\Documents\Arduino"
    goto menu
)
