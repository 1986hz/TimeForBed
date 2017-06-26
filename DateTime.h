#ifndef _DATETIME_H_
#define _DATETIME_H_

class DateTime
{
public:
	int hour;
	int min;
	int sec;

	bool isDayChanged;
	bool isMinChaanged;

	DateTime();
	void setDateTime(int hour, int min, int sec);
	void clearIsDayChanged();
	void clearIsMinChanged();
};

#endif