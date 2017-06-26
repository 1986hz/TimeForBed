// 
// 
// 

#include "WizFi310Helper.h"


#define BUFFER_SIZE (512)


WizFi310Helper::WizFi310Helper(HardwareSerial *serial)
{
	this->serial = serial;
}


// ssid의 수신강도를 리턴한다.
// 만일 scan이 되지 않으면 0을 리턴한다.
int WizFi310Helper::scan(char *ssid)
{
	char buffer[BUFFER_SIZE];
	String ssid_str = ssid;
	String command = "AT+WSCAN=" + ssid_str;
	command += '\r';

	serial->print(command);

	while (1) {
		if (serial->available()) {
			serial->readBytes(buffer, BUFFER_SIZE);
			break;
		}
	}

	char *result;
	char *result_end;
	result = strstr(buffer, "\r\n");
	result = result + 2;

	if (strstr(result, "[OK]") == result)
		return 0;

	// find rssi
	result = myStrstr(result, "/", 3);
	result++;

	result_end = strstr(result, "/");

	char rssi[5];
	for (int i = 0; i < 5; i++) {
		rssi[i] = *result;
		result++;
		if (result == result_end)
			break;
	}

	return atoi(rssi);
}


// WiFiProfileManager에 등록된 ssid중에서 수신강도가 제일 좋은 ssid의 index를 리턴한다.
// 만일 연결할 ssid가 없으면 -1을 리턴한다.
int WizFi310Helper::searchSsidToConnect(WiFiProfileManager *wpm)
{
	int wmp_count = wpm->getProfileCount();

	int max_rssi = -1000;
	profile pf;
	int ssid_index = -1;
	int result_rssi;
	
	for (int index = 0; index < wmp_count; index++) {
		pf = wpm->getProfile(index);
		result_rssi = scan(pf.ssid);

		Serial.println(pf.ssid);
		Serial.println(pf.password);
		Serial.println(result_rssi);

		if (result_rssi == 0)
			continue;
		if (result_rssi > max_rssi) {
			ssid_index = index;
			max_rssi = result_rssi;
		}
	}

	return ssid_index;
}


// s1에서 count번째 s2의 위치를 찾아 리턴한다.
char* WizFi310Helper::myStrstr(char *s1, char *s2, int count)
{
	char *result = s1;
	for (int i = 0; i < count; i++) {
		result = strstr(result, s2);
		result++;
	}

	return result-1;
}