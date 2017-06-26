#include "DateTime.h"


DateTime::DateTime()
{
	hour = 0;
	min = 0;
	sec = 0;
}


void DateTime::setDateTime(int hour, int min, int sec)
{
	// 0�ð� �Ǿ��� ��� 
	if (this->hour != 0 && hour == 0)
		isDayChanged = true;

	// �д����� ����Ǿ��� ���
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