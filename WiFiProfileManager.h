// WiFiProfileManager.h

#ifndef _WIFIPROFILEMANAGER_h
#define _WIFIPROFILEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define PROFILE_COUNT_MAX (5)
#define PROFILE_LEN_MAX (20)


typedef struct {
	char ssid[PROFILE_LEN_MAX];
	char password[PROFILE_LEN_MAX];
}profile;


class WiFiProfileManager
{
private:
	int profileCount;
	profile profileList[PROFILE_COUNT_MAX];
	int ssidAddressList[PROFILE_COUNT_MAX];
	int passwordAddressList[PROFILE_COUNT_MAX];
public:
	WiFiProfileManager();
	void readDataFromEEPROM();
	bool clearData();
	bool isFull();
	bool addProfile(profile *newProfile);
	bool deleteProfile(int index);
	bool setProfile(int index, profile *src);
	bool setProfileCount(int count);
	profile getProfile(int index);
	int getProfileCount();
	void myStrCpy(char *dest, const char *src);
};

#endif

