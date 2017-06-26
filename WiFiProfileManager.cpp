// 
// 
// 

#include "WiFiProfileManager.h"
#include <EEPROM.h>


// dest에 src를 복사한다.
void WiFiProfileManager::myStrCpy(char *dest, const char *src)
{
	for (int i = 0; i < PROFILE_LEN_MAX - 1; i++) {
		dest[i] = src[i];

		if (src[i] == NULL)
			return;
	}
	dest[PROFILE_LEN_MAX - 1] = NULL;
}


WiFiProfileManager::WiFiProfileManager()
{
	profileCount = 0;
	
	// ssid와 password를 저장할 EEPROM 주소를 리스트화 시킨다.
	for (int i = 0; i < PROFILE_COUNT_MAX; i++) {
		ssidAddressList[i] = PROFILE_LEN_MAX * 2 * i + 1;
		passwordAddressList[i] = PROFILE_LEN_MAX * 2 * i + PROFILE_LEN_MAX + 1;
	}

	readDataFromEEPROM();
}


bool WiFiProfileManager::clearData()
{
	setProfileCount(0);
}


void WiFiProfileManager::readDataFromEEPROM()
{
	profileCount = EEPROM.read(0);

	if (profileCount == 0)
		return;

	int i, j;
	for (i = 0; i < profileCount; i++) {
		for (j = 0; j < PROFILE_LEN_MAX; j++) {
			profileList[i].ssid[j] = EEPROM.read(ssidAddressList[i] + j);
			profileList[i].password[j] = EEPROM.read(passwordAddressList[i] + j);
		}
	}
}


bool WiFiProfileManager::isFull()
{
	if (profileCount == PROFILE_COUNT_MAX)
		return true;
	return false;
}


bool WiFiProfileManager::addProfile(profile *newProfile)
{
	if (isFull())
		return false;

	int newIndex = profileCount;
	setProfileCount(profileCount + 1);
	
	setProfile(newIndex, newProfile);
}


bool WiFiProfileManager::deleteProfile(int index)
{
	if (index == profileCount - 1) {
		setProfileCount(profileCount - 1);
		return 1;
	}

	for (int i = index; i < profileCount-1; i++) {
		setProfile(i, &profileList[i + 1]);
	}
	setProfileCount(profileCount - 1);
}


bool WiFiProfileManager::setProfile(int index, profile *src)
{
	myStrCpy(profileList[index].ssid, src->ssid);
	myStrCpy(profileList[index].password, src->password);

	for (int i = 0; i < PROFILE_LEN_MAX; i++) {
		EEPROM.write(ssidAddressList[index] + i, profileList[index].ssid[i]);
		EEPROM.write(passwordAddressList[index] + i, profileList[index].password[i]);
	}
}


bool WiFiProfileManager::setProfileCount(int count)
{
	profileCount = count;

	EEPROM.write(0, count);
}


profile WiFiProfileManager::getProfile(int index)
{
	if (index >= profileCount) {
		profile newProfile;
		newProfile.ssid[0] = NULL;
		newProfile.password[0] = NULL;

		return newProfile;
	}

	return profileList[index];
}

int WiFiProfileManager::getProfileCount()
{
	return profileCount;
}