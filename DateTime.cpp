#include "DateTime.h"


DateTime::DateTime()
{
	hour = 0;
	min = 0;
	sec = 0;
}


void DateTime::setDateTime(int hour, int min, int sec)
{
	// 0시가 되었을 경우 
	if (this->hour != 0 && hour == 0)
		isDayChanged = true;

	// 분단위가 변경되었을 경우
	if (this->min != min)
		isMinChaanged = true;

	this->hour = hour;
	this->min = min;
	this->sec = sec;
}


void DateTime::clearIsDayChanged()
{
	isDayChanged = false;
}


void DateTime::clearIsMinChanged()
{
	isMinChaanged = false;
}