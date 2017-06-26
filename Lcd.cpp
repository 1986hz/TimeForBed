// 
// 
// 

#include "Lcd.h"


LcdClass::LcdClass()
{
	_lcd = new LiquidCrystal_I2C(0x3F, 16, 2);
}


void LcdClass::init()
{
	
	_lcd->init();
}


void LcdClass::clear()
{
	_lcd->clear();
}


void LcdClass::printInit()
{
	_lcd->setCursor(0, 0);
	_lcd->print("Wating for Ready");
}


void LcdClass::printBackground()
{
	_lcd->setCursor(0, 0);
	_lcd->print("00:00     WiFi: ");
}


void LcdClass::printBluetoothConnecting()
{
	_lcd->setCursor(0, 0);
	_lcd->print("Bluetooth");
	_lcd->setCursor(0, 1);
	_lcd->print("connecting...");
}


void LcdClass::printTime(DateTime *currentTime)
{
	_lcd->setCursor(0, 0);
	if (currentTime->hour / 10 == 0)
		_lcd->print(0);
	_lcd->print(currentTime->hour);

	_lcd->setCursor(3, 0);
	if (currentTime->min / 10 == 0)
		_lcd->print(0);
	_lcd->print(currentTime->min);

	//_lcd->print(currentTime->sec);
}


void LcdClass::printWiFiStatus(int wifiStatus)
{
	_lcd->setCursor(15, 0);
	if (wifiStatus == 255) {
		_lcd->print("@");
	}
	else if (wifiStatus == 1) {
		_lcd->print("Y");
	}
	else {
		//long rssi = WiFi.RSSI();
		_lcd->print("N");
	}
}


void LcdClass::printTemperatureHumidity(float temperature, float humidity)
{
	_lcd->setCursor(0, 1);
	_lcd->print(temperature);
	_lcd->print("c ");
	_lcd->print(humidity);
	_lcd->print("%");
}


void LcdClass::backLight()
{
	_lcd->backlight();
}


void LcdClass::noBackLight()
{
	_lcd->noBacklight();
}


LcdClass Lcd;