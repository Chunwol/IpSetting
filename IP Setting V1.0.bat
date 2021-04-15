title 한세 IP 자동 설정(무선랜)
mode con cols=80 lines=35
@echo off
:main
cls
COLOR 0F
set menunr=GARBAGE
echo -------------------------------------------------------------------------------
echo                                  무선랜 자동 설정
echo                                  1: 고정 IP
echo                                  2: 동적 IP
echo                                  q: 종료(앱 종료)
echo                                  r: 재부팅(윈도우 재부팅)
echo                                  m: 만든사람
echo -------------------------------------------------------------------------------
SET /P sel=선택하세요:
IF %sel%==1 (goto gojung1)
IF %sel%==2 (goto dhcp)
IF %sel%==q (goto quit)
IF %sel%==r (goto restart)
IF %sel%==m (goto made)
:gojung1
set /a myNumber = %RANDOM% %% 254 + 1
echo 한세용 고정 IP를 설정합니다.
echo IP : 192.168.1.%myNumber%
echo subnet mask : 255.255.255.0
echo gateway : 192.168.1.1
netsh interface ip set address name="Wi-Fi" static 192.168.1.%myNumber% 255.255.255.0 192.168.1.1 1 
echo DNS : 8.8.8.8
netsh interface ip set dns name="Wi-Fi" static 8.8.8.8
echo 구성중입니다.....
ping   8.8.8.8   -n 5   >   nul
echo -------------------------------------------------------------------------------
echo 다음과 같이 설정이 완료되었습니다.
netsh interface ip show addresses "Wi-Fi"
echo -------------------------------------------------------------------------------
pause
goto quit
:dhcp
echo 동적 IP 할당모드로 설정합니다.
netsh interface ip set address name="Wi-Fi" dhcp
netsh interface ip set dns name="Wi-Fi" dhcp
echo 구성중입니다.....
ping   8.8.8.8   -n 5   >   nul
echo -------------------------------------------------------------------------------
echo 다음과 같이 설정이 완료되었습니다.
netsh interface ip show addresses "Wi-Fi"
echo -------------------------------------------------------------------------------
pause
goto quit
:restart
shutdown -r -t 0 
:made 
echo -------------------------------------------------------------------------------
echo                               H1226 황태우
echo -------------------------------------------------------------------------------
pause
goto main

:quit
echo 종료합니다.
exit 