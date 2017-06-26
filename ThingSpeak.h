// ThingSpeak.h

#ifndef _THINGSPEAK_h
#define _THINGSPEAK_h

#include <Arduino.h>
#include <WizFi310.h>

class ThingSpeak
{
public:
	ThingSpeak(String apiKey);
	void Update(String fieldValue1, String fieldValue2);

private:
	WiFiClient client;
	String apiKey;
};


#endif

