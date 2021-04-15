#include <stdlib.h>
#include <stdio.h>
#include<Windows.h>
#include <io.h>
#include<locale.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h> 
#define MAX_IP_SIZE 20
#define BUFF_SIZE 1024
char path[200];
char IP[MAX_IP_SIZE];
char StaticIP[MAX_IP_SIZE];
char Gateway[MAX_IP_SIZE];
char NetworkName[MAX_IP_SIZE];
char DNS1[MAX_IP_SIZE];
char DNS2[MAX_IP_SIZE];
char SearchSSID[MAX_IP_SIZE];
char Subnetmask[MAX_IP_SIZE];
char HistoryIP[MAX_IP_SIZE];
char** WiFiName;
char random[5] = "0";
int error = 0;

void SettingOutput();
void resetSetting();
void header();
void footer();
char* IPSearchname(void);
bool StaticIPSetting(void);
bool DHCPIPSetting(void);
bool wificonnect();
bool PingTest(void);

//지정된 SSID로 연결할수 있게 한 6개정도 가능하게 만들것!!
void SettingOutput() {
	WritePrivateProfileString(TEXT("IP"), TEXT("IP"), IP, path);
	WritePrivateProfileString(TEXT("IP"), TEXT("StaticIP"), StaticIP, path);
	WritePrivateProfileString(TEXT("IP"), TEXT("Subnetmask"), Subnetmask, path);
	WritePrivateProfileString(TEXT("IP"), TEXT("Gateway"), Gateway, path);
	WritePrivateProfileString(TEXT("IP"), TEXT("NetworkName"), NetworkName, path);
	WritePrivateProfileString(TEXT("Search"), TEXT("SSID"), SearchSSID, path);
	WritePrivateProfileString(TEXT("DNS"), TEXT("DNS1"), DNS1, path);
	WritePrivateProfileString(TEXT("DNS"), TEXT("DNS2"), DNS2, path);
	WritePrivateProfileString(TEXT("History"), TEXT("HistoryIP"), random, path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N1"), WiFiName[0], path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N2"), WiFiName[1], path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N3"), WiFiName[2], path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N4"), WiFiName[3], path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N5"), WiFiName[4], path);
	WritePrivateProfileString(TEXT("SSID"), TEXT("N6"), WiFiName[5], path);

};
void resetSetting() {
	strcpy_s(IP, MAX_IP_SIZE, "192.168.1.");
	strcpy_s(StaticIP, MAX_IP_SIZE, "0");
	strcpy_s(Subnetmask, MAX_IP_SIZE, "255.255.255.0");
	strcpy_s(Gateway, MAX_IP_SIZE, "192.168.1.1");
	strcpy_s(NetworkName, MAX_IP_SIZE, "Wi-Fi");
	strcpy_s(SearchSSID, MAX_IP_SIZE, "hsoc-");
	strcpy_s(DNS1, MAX_IP_SIZE, "8.8.8.8");
	strcpy_s(DNS2, MAX_IP_SIZE, "4.4.4.4");
	strcpy_s(HistoryIP, MAX_IP_SIZE, "0");
	strcpy_s(WiFiName[0], 10, "hsoc-21");
	strcpy_s(WiFiName[1], 10, "hsoc-22");
	strcpy_s(WiFiName[2], 10, "hsoc-32");
	strcpy_s(WiFiName[3], 10, "hsoc-33");
	strcpy_s(WiFiName[4], 10, "hsoc-42");
	strcpy_s(WiFiName[5], 10, "hsoc-43");
	SettingOutput();

}
void Setting() {
	//WIFIName malloc 선언

	WiFiName = (char**)malloc(6 * sizeof(char*));
	for (int i = 0; i < 6; i++) {
		WiFiName[i] = (char*)malloc(10 * sizeof(char));
	}



	GetEnvironmentVariable("APPDATA", path, sizeof(path));
	strcat_s(path, sizeof(path), "\\IPSetting");
	mkdir(path);
	strcat_s(path, sizeof(path), "\\Setting.ini");
	//printf("%s\n\n",path);
	if (_access(path, 0) == 0)
	{
		GetPrivateProfileString(TEXT("IP"), TEXT("IP"), "error", IP, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("IP"), TEXT("StaticIP"), "error", StaticIP, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("IP"), TEXT("Subnetmask"), "error", Subnetmask, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("IP"), TEXT("Gateway"), "error", Gateway, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("IP"), TEXT("NetworkName"), "error", NetworkName, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("Search"), TEXT("SSID"), "error", SearchSSID, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("DNS"), TEXT("DNS1"), "error", DNS1, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("DNS"), TEXT("DNS2"), "error", DNS2, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("History"), TEXT("HistoryIP"), "error", HistoryIP, MAX_IP_SIZE, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N1"), "error", WiFiName[0], 10, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N2"), "error", WiFiName[1], 10, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N3"), "error", WiFiName[2], 10, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N4"), "error", WiFiName[3], 10, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N5"), "error", WiFiName[4], 10, path);
		GetPrivateProfileString(TEXT("SSID"), TEXT("N6"), "error", WiFiName[5], 10, path);

		if (strcmp(IP, "error") == 0) {
			strcpy_s(IP, MAX_IP_SIZE, "192.168.1.");
			WritePrivateProfileString(TEXT("IP"), TEXT("IP"), IP, path);
		}
		if (strcmp(StaticIP, "error") == 0) {
			strcpy_s(DNS1, MAX_IP_SIZE, "0");
			WritePrivateProfileString(TEXT("IP"), TEXT("StaticIP"), StaticIP, path);
		}
		if (strcmp(Subnetmask, "error") == 0) {
			strcpy_s(Subnetmask, MAX_IP_SIZE, "255.255.255.0");
			WritePrivateProfileString(TEXT("IP"), TEXT("Subnetmask"), Subnetmask, path);
		}
		if (strcmp(Gateway, "error") == 0) {
			strcpy_s(Gateway, MAX_IP_SIZE, "192.168.1.1");
			WritePrivateProfileString(TEXT("IP"), TEXT("Gateway"), Gateway, path);
		}
		if (strcmp(NetworkName, "error") == 0) {
			strcpy_s(NetworkName, MAX_IP_SIZE, "Wi-Fi");
			WritePrivateProfileString(TEXT("IP"), TEXT("NetworkName"), NetworkName, path);
		}
		if (strcmp(SearchSSID, "error") == 0) {
			strcpy_s(SearchSSID, MAX_IP_SIZE, "hsoc-");
			WritePrivateProfileString(TEXT("Search"), TEXT("SSID"), Subnetmask, path);
		}
		if (strcmp(DNS1, "error") == 0) {
			strcpy_s(DNS1, MAX_IP_SIZE, "8.8.8.8");
			WritePrivateProfileString(TEXT("DNS"), TEXT("DNS1"), DNS1, path);
		}
		if (strcmp(DNS2, "error") == 0) {
			strcpy_s(DNS2, MAX_IP_SIZE, "4.4.4.4");
			WritePrivateProfileString(TEXT("DNS"), TEXT("DNS2"), DNS2, path);
		}
		if (strcmp(HistoryIP, "error") == 0) {
			strcpy_s(HistoryIP, MAX_IP_SIZE, "0");
			WritePrivateProfileString(TEXT("History"), TEXT("HistoryIP"), HistoryIP, path);
		}
		if (strcmp(WiFiName[0], "error") == 0) {
			strcpy_s(WiFiName[0], 10, "hsoc-21");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N1"), WiFiName[0], path);
		}
		if (strcmp(WiFiName[1], "error") == 0) {
			strcpy_s(WiFiName[1], 10, "hsoc-22");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N2"), WiFiName[1], path);
		}
		if (strcmp(WiFiName[2], "error") == 0) {
			strcpy_s(WiFiName[2], 10, "hsoc-32");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N3"), WiFiName[2], path);
		}
		if (strcmp(WiFiName[3], "error") == 0) {
			strcpy_s(WiFiName[3], 10, "hsoc-33");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N4"), WiFiName[3], path);
		}
		if (strcmp(WiFiName[4], "error") == 0) {
			strcpy_s(WiFiName[4], 10, "hsoc-42");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N5"), WiFiName[4], path);
		}
		if (strcmp(WiFiName[5], "error") == 0) {
			strcpy_s(WiFiName[5], 10, "hsoc-43");
			WritePrivateProfileString(TEXT("SSID"), TEXT("N6"), WiFiName[5], path);
		}
	}
	else {
		resetSetting();
	}
}

char* IPSearchname(void) {
	char* context = NULL;

	char  buff[BUFF_SIZE];
	FILE* fp;

	fp = _popen("netsh wlan show interface | find \"SSID\" | find /V \"BSSID\"", "r");
	if (NULL == fp)
	{
		printf("popen() 실패");
		return 0;
	}
	while (fgets(buff, BUFF_SIZE, fp)) {
		//printf("%s\n", buff);
	}

	char* str = strrchr(buff, ': ');
	//printf("%s", str);
	if (str == NULL) {
		return 0;
	}
	char* SSID[50];

	strncpy_s(SSID, sizeof(SSID), str + 1, strlen(str) - 2);
	//printf("\"!!!!%s!!!!\"\n", SSID);
	_pclose(fp);
	return SSID;

}

bool StaticIPSetting(void) {
	char* ipname;
	ipname = IPSearchname();
	//printf("\n%s\n", ipname);
	if (ipname == NULL) {
		printf("와이파이 연결 안되어 있습니다.\n연결하는 페이지로 이동합니다...\n\n");
		system("pause");
		if (!wificonnect()) {
			return false;
		}
		ipname = IPSearchname();
	}
	printf_s("인터넷 연결 확인중...");
	if (PingTest()) {
		printf_s("\n이미 인터넷에 연결이 되어 있습니다...\n\n");
		return false;
	}

	if (!strcmp(StaticIP, "0") == 0 && strcmp(random, "0") == 0) {
		strcpy_s(random, sizeof(random), StaticIP);
	}
	else if (!strcmp(HistoryIP, "0") == 0) {
		strcpy_s(random, sizeof(random), HistoryIP);
		strcpy_s(HistoryIP, sizeof(HistoryIP), "0");
	}
	else {
		sprintf_s(random, sizeof(random), "%d", ((rand() % 253) + 2));
	}
	char  buff[BUFF_SIZE];
	FILE* fp;
	char* cmd[100];

	printf_s("[%s%s] 아이피 설정 중...\n", IP, random);
	sprintf_s(cmd, sizeof(cmd), "netsh -c int ip set address name = \"%s\" source = static addr = %s%s mask = %s gateway = %s gwmetric = 0", NetworkName, IP, random, Subnetmask, Gateway);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n 재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}
	//Sleep(1000);
	//printf_s("아이피 설정 완료. \n\n\n주 DNS설정중...\n");
	//Sleep(1000);
	sprintf_s(cmd, sizeof(cmd), "netsh -c int ip set dns name = \"%s\" source = static addr = %s register = PRIMARY no", NetworkName, DNS1);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n 재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}
	//printf_s("주 DNS설정 완료. \n\n\n보조 DNS설정중...\n");
	//Sleep(1000);
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip add dnsservers \"%s\" index=2 %s", NetworkName, DNS2);
	//printf_s("%s\n", &cmd);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n 재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}

	//printf_s("보조 DNS설정 완료. \n\n\n인터넷 연결 대기중...\n");
	Sleep(6000);
	printf_s("[%s%s] 인터넷 연결 확인중...\n", IP, random);
	if (!PingTest()) {
		//system("pause");
		error++;
		if (error == 3) {
			printf_s("재시도 횟수가 3회 입니다.\n WIFI를 재시작 합니다..\n\n");
			sprintf_s(cmd, sizeof(cmd), "netsh interface set interface \"%s\" disabled", NetworkName);
			fp = _popen(cmd, "r");
			if (NULL == fp)
			{
				printf("popen() 실패");
				return false;
			}
			sprintf_s(cmd, sizeof(cmd), "netsh interface set interface \"%s\" enable", NetworkName);
			fp = _popen(cmd, "r");
			if (NULL == fp)
			{
				printf("popen() 실패");
				return false;
			}
			//resetSetting();
			//return false;
		}
		else if (error == 6) {
			printf_s("재시도 횟수가 6회 이상입니다.\n프로그램을 초기화합니다..\n\n");
			resetSetting();
			return false;
		}
		else {
			printf_s("인터넷 연결에 실패하였습니다.\n다시 시도합니다...\n\n");
		}
		if (!StaticIPSetting()) {
			return false; //확인해봐야함.
		}
	}
	_pclose(fp);
	return true;
}
bool DHCPIPSetting(void) {
	FILE* fp;
	char* cmd[100];
	printf_s("DHCP 설정중...\n\n");
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip set address \"%s\" dhcp", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip set dns \"%s\" dhcp", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}
	//printf_s("DHCP 갱신...\n\n");
	sprintf_s(cmd, sizeof(cmd), "ipconfig /renew \"%s\"", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("오류!!! 설정 파일을 초기화합니다.\n재시작 해서 다시 시도해 주십시오...\n\n");
		resetSetting();
		return false;
	}
	printf_s("DHCP 설정완료.\n\n\n");
	return true;
}

bool wificonnect() {
	char  buff[BUFF_SIZE];
	FILE* fp;
	char* cmd[100];

	sprintf_s(cmd, sizeof(cmd), "netsh wlan show networks | find \"%s\"", SearchSSID);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf("popen() 실패");
		return 0;
	}

	char str[20];
	char** SSID;
	SSID = (char**)malloc(6 * sizeof(char*));
	for (int i = 0; i < 6; i++) {
		SSID[i] = (char*)malloc(10 * sizeof(char));
	}
	int i = 0;
	int j = 0;
	header();
	while (fgets(buff, BUFF_SIZE, fp)) {
		char* ptr = strstr(buff, " : ");
		strncpy_s(str, sizeof(str), ptr + 3, strlen(ptr));
		printf_s(" │ %d : Wifi연결 : %s", i + 1, &str);
		printf_s(" │\n");
		strcpy_s(SSID[i], 10, str);
		i++;
		if (i == 3)
			break;
	}
	if (i == 0) {
		printf_s(" │ 와이파이가 검색되지 않습니다. \n");
		printf_s(" │\n");
	}
	printf_s(" │ 4 : 지정된 와이파이! \n");

	footer();

	//if (i == 0) {
	//	return false;
	//}
	//getchar();
	fflush(stdin);
	char menu = '1';
	printf_s("\n선택[Enter] : ");
	rewind(stdin);
	scanf_s("%c", &menu, sizeof(menu));
	int num;

	switch (menu)
	{
	case '1':
		if (i == 0) {
			printf_s("잘못 입력하셨습니다.\n");
			system("pause");
			if (!wificonnect()) {
				return false;
			}
			return true;
		}
		num = 0;
		break;
	case '2':
		if (i < 2) {
			printf_s("잘못 입력하셨습니다.\n");
			system("pause");
			if (!wificonnect()) {
				return false;
			}
			return true;
		}
		num = 1;
		break;
	case '3':
		if (i < 3) {
			printf_s("잘못 입력하셨습니다.\n");
			system("pause");
			if (!wificonnect()) {
				return false;
			}
			return true;
		}
		num = 2;
		break;
	case '4':
		while (true) {
			j = 0;
			header();
			for (int i = 0; i < 6; i++) {
				if (!(*WiFiName[i] == NULL)) {
					printf_s(" │ %d : Wifi연결 : %s\n", j + 1, WiFiName[i]);
					printf_s(" │\n");
					strcpy_s(SSID[j], 10, WiFiName[i]);
					j++;
				}
			}
			footer();

			printf_s("\n선택[Enter] : ");
			int select = 1;
			fflush(stdin);
			scanf_s("%d", &select);

			if (select <= j && select > 0) {
				num = select - 1;
				break;
			}
			else {
				printf_s("잘못 입력하셨습니다.\n");
			}

		}
		break;
	default:
		printf_s("잘못 입력하셨습니다.\n");
		system("pause");
		if (!wificonnect()) {
			return false;
		}
		return true;
	}

	printf_s("현재 연결 시도할 와이파이 : %s\n", SSID[num]);
	printf_s("와이파이 연결중..\n");
	//
	//system("pause");
	//
	sprintf_s(cmd, sizeof(cmd), "netsh wlan connect name=%s", SSID[num]);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf("popen() 실패");
		return false;
	}
	Sleep(5000);
	char* ipname;
	ipname = IPSearchname();
	if (ipname == NULL) {
		printf_s("연결 실패!! 수동으로 연결후 프로그램을 다시 시작해 주세요.\n\n");
		return false;
	}
	printf_s("연결 성공\n\n");
	_pclose(fp);
	return true;
}

bool PingTest(void) {
	int num = 0;
	printf_s("\n\n");
	for (int i = 0; i <= 2; i++)
	{
		if (system("ping 8.8.8.8 -n 1 -w 5 | find \"응답:\" | find \"바이트\"") == 1) {
			printf("요청 시간이 만료되었습니다.\n");
			num++;
		}
		else {
			return true;
		}
		if (num >= 2) {
			return false;
		}
	}
	return true;
}
void header() {
	system("cls");
	printf_s(" ┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf_s(" │ \t\t\t* 아이피 설정 프로그램 V2.5 *\n");
	printf_s(" │\n");
}
void footer() {
	printf_s(" │\n");
	printf_s(" ├━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf_s(" │ 이 프로그램의 저작권자는 임석현 입니다.\n");
	printf_s(" │ 이 프로그램의 무단 배포를 금지합니다.\n");
	printf_s(" │ 제작자 디스코드 : 천월#1465\n");
	printf_s(" │ 제작자 이메일 : chunwol@kakao.com\n");
	printf_s(" ┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}
int main() {

	Setting();
	//wificonnect();
	//system("pause");
	srand(time(NULL));
	FILE* fp;
	char* cmd[100];
	sprintf_s(cmd, sizeof(cmd), "netsh interface set interface \"%s\" enable", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf("popen() 실패");
		return false;
	}

	header();
	printf_s(" │ 1 : Static IP 설정(기본)\n");
	printf_s(" │\n");
	printf_s(" │ 2 : DHCP IP 설정\n");
	printf_s(" │\n");
	printf_s(" │ 3 : 설정 변경\n");
	printf_s(" │\n");
	printf_s(" │ 4 : 종료\n");
	footer();
	printf_s("선택[Enter] : ");
	char menu = getchar();
	switch (menu)
	{
	case '1':
		if (StaticIPSetting()) {
			printf_s("인터넷 연결에 성공하였습니다.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n프로그램을 종료합니다...\n\n");
			SettingOutput();
		}
		system("pause");
		//system("pause");
		break;
	case '2':
		if (DHCPIPSetting()) {
			printf_s("인터넷 연결에 성공하였습니다.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n프로그램을 종료합니다...\n\n");
			//SettingOutput();
		}
		system("pause");
		break;
	case '3':
		system(path);
		//system("pause");
		break;
	case '4':
		break;
	default:
		if (StaticIPSetting()) {
			printf_s("인터넷 연결에 성공하였습니다.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n프로그램을 종료합니다...\n\n");
			SettingOutput();
		}
		system("pause");
		break;
	}
	return 0;
}