title �Ѽ� IP �ڵ� ����(������)
mode con cols=80 lines=35
@echo off
:main
cls
COLOR 0F
set menunr=GARBAGE
echo -------------------------------------------------------------------------------
echo                                  ������ �ڵ� ����
echo                                  1: ���� IP
echo                                  2: ���� IP
echo                                  q: ����(�� ����)
echo                                  r: �����(������ �����)
echo                                  m: ������
echo -------------------------------------------------------------------------------
SET /P sel=�����ϼ���:
IF %sel%==1 (goto gojung1)
IF %sel%==2 (goto dhcp)
IF %sel%==q (goto quit)
IF %sel%==r (goto restart)
IF %sel%==m (goto made)
:gojung1
set /a myNumber = %RANDOM% %% 254 + 1
echo �Ѽ��� ���� IP�� �����մϴ�.
echo IP : 192.168.1.%myNumber%
echo subnet mask : 255.255.255.0
echo gateway : 192.168.1.1
netsh interface ip set address name="Wi-Fi" static 192.168.1.%myNumber% 255.255.255.0 192.168.1.1 1 
echo DNS : 8.8.8.8
netsh interface ip set dns name="Wi-Fi" static 8.8.8.8
echo �������Դϴ�.....
ping   8.8.8.8   -n 5   >   nul
echo -------------------------------------------------------------------------------
echo ������ ���� ������ �Ϸ�Ǿ����ϴ�.
netsh interface ip show addresses "Wi-Fi"
echo -------------------------------------------------------------------------------
pause
goto quit
:dhcp
echo ���� IP �Ҵ���� �����մϴ�.
netsh interface ip set address name="Wi-Fi" dhcp
netsh interface ip set dns name="Wi-Fi" dhcp
echo �������Դϴ�.....
ping   8.8.8.8   -n 5   >   nul
echo -------------------------------------------------------------------------------
echo ������ ���� ������ �Ϸ�Ǿ����ϴ�.
netsh interface ip show addresses "Wi-Fi"
echo -------------------------------------------------------------------------------
pause
goto quit
:restart
shutdown -r -t 0 
:made 
echo -------------------------------------------------------------------------------
echo                               H1226 Ȳ�¿�
echo -------------------------------------------------------------------------------
pause
goto main

:quit
echo �����մϴ�.
exit 