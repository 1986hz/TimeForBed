// WizFi310Helper.h

#ifndef _WIZFI310HELPER_h
#define _WIZFI310HELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include <Arduino.h>
#include "WiFiProfileManager.h"


class WizFi310Helper
{
public:
	WizFi310Helper(HardwareSerial *serial);
	int scan(char *ssid);
	int searchSsidToConnect(WiFiProfileManager *wpm);
	char* myStrstr(char *s1, char *s2, int count);

private:
	HardwareSerial *serial;
};


#endif

