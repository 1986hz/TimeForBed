// UserInterface.h

#ifndef _USERINTERFACE_h
#define _USERINTERFACE_h


#include "WiFiProfileManager.h"
#include <SoftwareSerial.h>


class UserInterface
{
public:
	UserInterface(SoftwareSerial *swSerial, WiFiProfileManager *wpm);
	int isCalled();
	void flushRead();
	void start();
	void selectShowProfile();
	void selectAddProfile();
	void selectDeleteProfile();
	void selectModifyProfile();
	void selectReset();

private:
	WiFiProfileManager *wpm;
	SoftwareSerial *swSerial;

	void getString(String *str);
	int getIndex();
	void getProfile(profile *pf);
};
#endif

