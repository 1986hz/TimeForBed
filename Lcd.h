// Lcd.h

#ifndef _LCD_h
#define _LCD_h

#include "DateTime.h"
#include "LiquidCrystal_I2C.h"


class LcdClass
{
 protected:
	 LiquidCrystal_I2C *_lcd;

 public:
	LcdClass();
	void init();
	void clear();
	void printInit();
	void printBackground();
	void printBluetoothConnecting();
	void printTime(DateTime *currentTime);
	void printWiFiStatus(int wifiStatus);
	void printTemperatureHumidity(float temperature, float humidity);

	void backLight();
	void noBackLight();
};

extern LcdClass Lcd;

#endif

