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

String thingSpeakApiKey = "";	// ThingSpeakApiKey 입력하기
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

	// 인터넷 연결을 시도하기
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
	// 현재 인터넷 연결 상태를 얻고, LCD에 표시
	wifiStatus = WiFi.status();
	Lcd.printWiFiStatus(WiFi.status());

	// 현재 시간을 얻고, LCD에 표시
	ds1307.getDateTime(&currentTime);
	Lcd.printTime(&currentTime);

	// 현재 온습도 정보를 얻고, LCD에 표시
	getTemperatureHumidityData();
	Lcd.printTemperatureHumidity(temperature, humidity);

	// 인터넷이 연결되어 있으면...
	if (wifiStatus == WL_CONNECTED) {
		// 분 단위가 변경되었을 경우, ThingSpeak에 온습도 정보 보내기
		if (currentTime.isMinChaanged) {
			Serial.println("Min changed");
			thingSpeak.Update(String(temperature), String(humidity));
			currentTime.clearIsMinChanged();
		}
		// 0시가 되었으면, NTPClient로 서버시간을 가져와서 현재시간 수정하기
		if (currentTime.isDayChanged) {
			Serial.println("Day changed");
			resetCurrentTimeFromNTPClient();
			currentTime.clearIsDayChanged();
		}
	}
	// 인터넷이 연결되지 않았으면, 인터넷연결 시도하기
	else if (wifiStatus != WL_NO_SHIELD) {
		connectWiFi();
		if (wifiStatus == WL_CONNECTED)
			resetCurrentTimeFromNTPClient();
	}

	// 블루투스로부터 입력이 있으면 ui로 통신하기
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