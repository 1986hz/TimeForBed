#ifndef _NTPCLIENT_h
#define _NTPCLIENT_h

#include "DateTime.h"
#include <WizFi310.h>
#include <WizFi310Udp.h>

class NTPClientClass
{
public:
	void init(WizFi310Class *wifi);
	int getDateTime(DateTime *dateTime);

private:
	WizFi310Class* _wifi;
};

extern NTPClientClass NTPClient;

#endif