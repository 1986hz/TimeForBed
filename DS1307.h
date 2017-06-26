// DS1307.h

#ifndef _DS1307_h
#define _DS1307_h

#include <Wire.h>
#include "DateTime.h"

class DS1307
{
public:
	DS1307();
	void setDateTime(DateTime *dateTime);
	void getDateTime(DateTime *dateTime);
	
	int decToBcd(int dec);
	int bcdToDec(int bcd);
};


#endif

