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

//������ SSID�� �����Ҽ� �ְ� �� 6������ �����ϰ� �����!!
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
	//WIFIName malloc ����

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
		printf("popen() ����");
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
		printf("�������� ���� �ȵǾ� �ֽ��ϴ�.\n�����ϴ� �������� �̵��մϴ�...\n\n");
		system("pause");
		if (!wificonnect()) {
			return false;
		}
		ipname = IPSearchname();
	}
	printf_s("���ͳ� ���� Ȯ����...");
	if (PingTest()) {
		printf_s("\n�̹� ���ͳݿ� ������ �Ǿ� �ֽ��ϴ�...\n\n");
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

	printf_s("[%s%s] ������ ���� ��...\n", IP, random);
	sprintf_s(cmd, sizeof(cmd), "netsh -c int ip set address name = \"%s\" source = static addr = %s%s mask = %s gateway = %s gwmetric = 0", NetworkName, IP, random, Subnetmask, Gateway);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n ����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}
	//Sleep(1000);
	//printf_s("������ ���� �Ϸ�. \n\n\n�� DNS������...\n");
	//Sleep(1000);
	sprintf_s(cmd, sizeof(cmd), "netsh -c int ip set dns name = \"%s\" source = static addr = %s register = PRIMARY no", NetworkName, DNS1);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n ����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}
	//printf_s("�� DNS���� �Ϸ�. \n\n\n���� DNS������...\n");
	//Sleep(1000);
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip add dnsservers \"%s\" index=2 %s", NetworkName, DNS2);
	//printf_s("%s\n", &cmd);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n ����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}

	//printf_s("���� DNS���� �Ϸ�. \n\n\n���ͳ� ���� �����...\n");
	Sleep(6000);
	printf_s("[%s%s] ���ͳ� ���� Ȯ����...\n", IP, random);
	if (!PingTest()) {
		//system("pause");
		error++;
		if (error == 3) {
			printf_s("��õ� Ƚ���� 3ȸ �Դϴ�.\n WIFI�� ����� �մϴ�..\n\n");
			sprintf_s(cmd, sizeof(cmd), "netsh interface set interface \"%s\" disabled", NetworkName);
			fp = _popen(cmd, "r");
			if (NULL == fp)
			{
				printf("popen() ����");
				return false;
			}
			sprintf_s(cmd, sizeof(cmd), "netsh interface set interface \"%s\" enable", NetworkName);
			fp = _popen(cmd, "r");
			if (NULL == fp)
			{
				printf("popen() ����");
				return false;
			}
			//resetSetting();
			//return false;
		}
		else if (error == 6) {
			printf_s("��õ� Ƚ���� 6ȸ �̻��Դϴ�.\n���α׷��� �ʱ�ȭ�մϴ�..\n\n");
			resetSetting();
			return false;
		}
		else {
			printf_s("���ͳ� ���ῡ �����Ͽ����ϴ�.\n�ٽ� �õ��մϴ�...\n\n");
		}
		if (!StaticIPSetting()) {
			return false; //Ȯ���غ�����.
		}
	}
	_pclose(fp);
	return true;
}
bool DHCPIPSetting(void) {
	FILE* fp;
	char* cmd[100];
	printf_s("DHCP ������...\n\n");
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip set address \"%s\" dhcp", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}
	sprintf_s(cmd, sizeof(cmd), "netsh interface ip set dns \"%s\" dhcp", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}
	//printf_s("DHCP ����...\n\n");
	sprintf_s(cmd, sizeof(cmd), "ipconfig /renew \"%s\"", NetworkName);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf_s("����!!! ���� ������ �ʱ�ȭ�մϴ�.\n����� �ؼ� �ٽ� �õ��� �ֽʽÿ�...\n\n");
		resetSetting();
		return false;
	}
	printf_s("DHCP �����Ϸ�.\n\n\n");
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
		printf("popen() ����");
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
		printf_s(" �� %d : Wifi���� : %s", i + 1, &str);
		printf_s(" ��\n");
		strcpy_s(SSID[i], 10, str);
		i++;
		if (i == 3)
			break;
	}
	if (i == 0) {
		printf_s(" �� �������̰� �˻����� �ʽ��ϴ�. \n");
		printf_s(" ��\n");
	}
	printf_s(" �� 4 : ������ ��������! \n");

	footer();

	//if (i == 0) {
	//	return false;
	//}
	//getchar();
	fflush(stdin);
	char menu = '1';
	printf_s("\n����[Enter] : ");
	rewind(stdin);
	scanf_s("%c", &menu, sizeof(menu));
	int num;

	switch (menu)
	{
	case '1':
		if (i == 0) {
			printf_s("�߸� �Է��ϼ̽��ϴ�.\n");
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
			printf_s("�߸� �Է��ϼ̽��ϴ�.\n");
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
			printf_s("�߸� �Է��ϼ̽��ϴ�.\n");
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
					printf_s(" �� %d : Wifi���� : %s\n", j + 1, WiFiName[i]);
					printf_s(" ��\n");
					strcpy_s(SSID[j], 10, WiFiName[i]);
					j++;
				}
			}
			footer();

			printf_s("\n����[Enter] : ");
			int select = 1;
			fflush(stdin);
			scanf_s("%d", &select);

			if (select <= j && select > 0) {
				num = select - 1;
				break;
			}
			else {
				printf_s("�߸� �Է��ϼ̽��ϴ�.\n");
			}

		}
		break;
	default:
		printf_s("�߸� �Է��ϼ̽��ϴ�.\n");
		system("pause");
		if (!wificonnect()) {
			return false;
		}
		return true;
	}

	printf_s("���� ���� �õ��� �������� : %s\n", SSID[num]);
	printf_s("�������� ������..\n");
	//
	//system("pause");
	//
	sprintf_s(cmd, sizeof(cmd), "netsh wlan connect name=%s", SSID[num]);
	fp = _popen(cmd, "r");
	if (NULL == fp)
	{
		printf("popen() ����");
		return false;
	}
	Sleep(5000);
	char* ipname;
	ipname = IPSearchname();
	if (ipname == NULL) {
		printf_s("���� ����!! �������� ������ ���α׷��� �ٽ� ������ �ּ���.\n\n");
		return false;
	}
	printf_s("���� ����\n\n");
	_pclose(fp);
	return true;
}

bool PingTest(void) {
	int num = 0;
	printf_s("\n\n");
	for (int i = 0; i <= 2; i++)
	{
		if (system("ping 8.8.8.8 -n 1 -w 5 | find \"����:\" | find \"����Ʈ\"") == 1) {
			printf("��û �ð��� ����Ǿ����ϴ�.\n");
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
	printf_s(" �Ȧ�����������������������������������������������������������������������������������������������������������������������������������\n");
	printf_s(" �� \t\t\t* ������ ���� ���α׷� V2.5 *\n");
	printf_s(" ��\n");
}
void footer() {
	printf_s(" ��\n");
	printf_s(" ��������������������������������������������������������������������������������������������������������������������������������������\n");
	printf_s(" �� �� ���α׷��� ���۱��ڴ� �Ӽ��� �Դϴ�.\n");
	printf_s(" �� �� ���α׷��� ���� ������ �����մϴ�.\n");
	printf_s(" �� ������ ���ڵ� : õ��#1465\n");
	printf_s(" �� ������ �̸��� : chunwol@kakao.com\n");
	printf_s(" �Ʀ�����������������������������������������������������������������������������������������������������������������������������������\n");
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
		printf("popen() ����");
		return false;
	}

	header();
	printf_s(" �� 1 : Static IP ����(�⺻)\n");
	printf_s(" ��\n");
	printf_s(" �� 2 : DHCP IP ����\n");
	printf_s(" ��\n");
	printf_s(" �� 3 : ���� ����\n");
	printf_s(" ��\n");
	printf_s(" �� 4 : ����\n");
	footer();
	printf_s("����[Enter] : ");
	char menu = getchar();
	switch (menu)
	{
	case '1':
		if (StaticIPSetting()) {
			printf_s("���ͳ� ���ῡ �����Ͽ����ϴ�.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n���α׷��� �����մϴ�...\n\n");
			SettingOutput();
		}
		system("pause");
		//system("pause");
		break;
	case '2':
		if (DHCPIPSetting()) {
			printf_s("���ͳ� ���ῡ �����Ͽ����ϴ�.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n���α׷��� �����մϴ�...\n\n");
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
			printf_s("���ͳ� ���ῡ �����Ͽ����ϴ�.\n");
			sprintf_s(cmd, sizeof(cmd), "netsh -c int ip show address \"%s\"", NetworkName);
			system(cmd);
			printf_s("\n���α׷��� �����մϴ�...\n\n");
			SettingOutput();
		}
		system("pause");
		break;
	}
	return 0;
}