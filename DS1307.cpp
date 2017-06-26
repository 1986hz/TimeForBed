// 
// 
// 

#include <Arduino.h>
#include "DS1307.h"
#define ADDRESS (0X68)

DS1307::DS1307()
{
	Wire.begin();
}


void DS1307::setDateTime(DateTime *dateTime)
{
	Wire.beginTransmission(ADDRESS);
	Wire.write(0x00);
	Wire.write(decToBcd(dateTime->sec));
	Wire.write(decToBcd(dateTime->min));
	Wire.write(decToBcd(dateTime->hour));
	Wire.endTransmission();
}


void DS1307::getDateTime(DateTime *dateTime)
{
	int hour, min, sec;

	Wire.beginTransmission(ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();
	Wire.requestFrom(ADDRESS, 3);
	sec = bcdToDec(Wire.read());
	min = bcdToDec(Wire.read());
	hour = bcdToDec(Wire.read());

	dateTime->setDateTime(hour, min, sec);
}


int DS1307::decToBcd(int dec)
{
	return ((dec / 10 * 16) + (dec % 10));
}


int DS1307::bcdToDec(int bcd)
{
	return ((bcd / 16 * 10) + (bcd % 16));
}