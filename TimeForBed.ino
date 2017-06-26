#include "WizFi310Helper.h"
#include "UserInterface.h"
#include "WiFiProfileManager.h"
#include "DS1307.h"
#include "Lcd.h"
#include "NTPClient.h"
#include "DateTime.h"
#include "DS1307.h"
#include "ThingSpeak.h"
#include <WizFi310.h>
#include <DHT.h>
#include <SoftwareSerial.h>

#define bluetoothTx (10)
#define bluetoothRx (11)
#define dht22Input (7)


WiFiProfileManager wpm;
WizFi310Helper wifiHelper(&Serial3);

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
UserInterface ui(&bluetooth, &wpm);

DHT dht(dht22Input, DHT22);
float humidity;
float temperature;

DateTime currentTime;
DS1307 ds1307;

int wifiStatus;

String thingSpeakApiKey = "";	// ThingSpeakApiKey �Է��ϱ�
ThingSpeak thingSpeak(thingSpeakApiKey);


void setup()
{
	Lcd.init();
	Lcd.printInit();
	Lcd.backLight();

	dht.begin();

	bluetooth.begin(9600);
	
	Serial.begin(9600);
	Serial3.begin(115200);
	WiFi.init(&Serial3);
	NTPClient.init(&WiFi);

	// ���ͳ� ������ �õ��ϱ�
	wifiStatus = WiFi.status();
	if (wifiStatus != WL_CONNECTED && wifiStatus != WL_NO_SHIELD) {
		connectWiFi();
		if (wifiStatus == WL_CONNECTED)
			resetCurrentTimeFromNTPClient();
	}
	
	Lcd.printBackground();
}


void loop()
{
	// ���� ���ͳ� ���� ���¸� ���, LCD�� ǥ��
	wifiStatus = WiFi.status();
	Lcd.printWiFiStatus(WiFi.status());

	// ���� �ð��� ���, LCD�� ǥ��
	ds1307.getDateTime(&currentTime);
	Lcd.printTime(&currentTime);

	// ���� �½��� ������ ���, LCD�� ǥ��
	getTemperatureHumidityData();
	Lcd.printTemperatureHumidity(temperature, humidity);

	// ���ͳ��� ����Ǿ� ������...
	if (wifiStatus == WL_CONNECTED) {
		// �� ������ ����Ǿ��� ���, ThingSpeak�� �½��� ���� ������
		if (currentTime.isMinChaanged) {
			Serial.println("Min changed");
			thingSpeak.Update(String(temperature), String(humidity));
			currentTime.clearIsMinChanged();
		}
		// 0�ð� �Ǿ�����, NTPClient�� �����ð��� �����ͼ� ����ð� �����ϱ�
		if (currentTime.isDayChanged) {
			Serial.println("Day changed");
			resetCurrentTimeFromNTPClient();
			currentTime.clearIsDayChanged();
		}
	}
	// ���ͳ��� ������� �ʾ�����, ���ͳݿ��� �õ��ϱ�
	else if (wifiStatus != WL_NO_SHIELD) {
		connectWiFi();
		if (wifiStatus == WL_CONNECTED)
			resetCurrentTimeFromNTPClient();
	}

	// ��������κ��� �Է��� ������ ui�� ����ϱ�
	if (ui.isCalled()) {
		startUi();
	}

	delay(500);
}


void getTemperatureHumidityData()
{
	humidity = dht.readHumidity();
	temperature = dht.readTemperature();
}


void resetCurrentTimeFromNTPClient()
{
	NTPClient.getDateTime(&currentTime);
	ds1307.setDateTime(&currentTime);
}


void connectWiFi()
{
	int profile_index = wifiHelper.searchSsidToConnect(&wpm);
	if (profile_index == -1)
		return;
	profile pf = wpm.getProfile(profile_index);
	wifiStatus = WiFi.begin(pf.ssid, pf.password);
}


void startUi()
{
	Lcd.clear();
	Lcd.printBluetoothConnecting();
	ui.flushRead();
	ui.start();
	connectWiFi();
	Lcd.clear();
	Lcd.printBackground();
}