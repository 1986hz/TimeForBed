// 
// 
// 

#include "UserInterface.h"
#include <Arduino.h>


UserInterface::UserInterface(SoftwareSerial *swSerial, WiFiProfileManager *wpm)
{
	this->swSerial = swSerial;
	this->wpm = wpm;
}


void UserInterface::start()
{
	String selectedMenu = "";
	while (true) {
		swSerial->print("> Main\n1. Show profile\n2. Add profile\n");
		swSerial->print("3. Delete profile\n4. Modify profile\n");
		swSerial->print("5. Reset\n6. Exit\nSelect Menu (1.~6.):\n");
		swSerial->print("ends with .(period);");
		swSerial->flush();

		getString(&selectedMenu);

		if (selectedMenu.equals("1"))
			selectShowProfile();
		else if (selectedMenu.equals("2"))
			selectAddProfile();
		else if (selectedMenu.equals("3"))
			selectDeleteProfile();
		else if (selectedMenu.equals("4"))
			selectModifyProfile();
		else if (selectedMenu.equals("5"))
			selectReset();
		else if (selectedMenu.equals("6")) {
			swSerial->print("Good bye :);");
			return;
		}
	}
}


void UserInterface::selectShowProfile()
{
	profile pf;
	swSerial->print("index / ssid / password\n");
	for (int i = 0; i < wpm->getProfileCount(); i++) {
		pf = wpm->getProfile(i);
		swSerial->print(i);
		swSerial->print(" / ");
		swSerial->print(pf.ssid);
		swSerial->print(" / ");
		swSerial->print(pf.password);
		swSerial->print('\n');
	}
	swSerial->print(';');
	swSerial->flush();
}


void UserInterface::selectAddProfile()
{
	if (wpm->isFull()) {
		swSerial->print("Profile is full;");
			return;
	}

	swSerial->print("> Main > Add profile\n");

	profile pf;
	getProfile(&pf);

	wpm->addProfile(&pf);
}


void UserInterface::selectDeleteProfile()
{
	swSerial->print("> main > Delete profile\n");
	swSerial->print("Input index for deleting :\n");
	swSerial->print("ends with .(period);");
	swSerial->flush();

	int index = getIndex();
	if (index == -1) {
		swSerial->print("Error index;");
		return;
	}
	
	wpm->deleteProfile(index);
	swSerial->print("Success to delete;");
}


void UserInterface::selectModifyProfile()
{
	swSerial->print("> main > Modify profile\n");
	swSerial->print("Input index for modifying :\n");
	swSerial->print("ends with .(period);");

	int index = getIndex();
	if (index == -1) {
		swSerial->print("Error index;");
		return;
	}

	profile pf;
	getProfile(&pf);

	wpm->setProfile(index, &pf);
	swSerial->print("Success to modify;");
}


void UserInterface::selectReset()
{
	wpm->clearData();
	swSerial->print("Success to reset;");
}


// swSerial로부터 문자열을 가져온다.
void UserInterface::getString(String *str)
{
	*str = "";
	char ch;

	while (true) {
		if (swSerial->available()) {
			ch = swSerial->read();
			if (ch == '.')
				break;
			*str += ch;
		}
	}
}


// swSerial로부터 정수를 가져온다.
int UserInterface::getIndex()
{
	String str;
	getString(&str);

	int index = str.toInt();

	if (index < 0 || index >= wpm->getProfileCount())
		return -1;

	return index;
}


void UserInterface::getProfile(profile * pf)
{
	String str;
	swSerial->print("Input SSID :\n");
	swSerial->print("ends with .(period);");
	swSerial->flush();

	getString(&str);
	str.toCharArray(pf->ssid, 20);

	swSerial->print("Input PASSWORD : \n");
	swSerial->print("ends with .(period);");

	getString(&str);
	str.toCharArray(pf->password, 20);
}


// swSerial로 입력받은 정보를 제거한다.
void UserInterface::flushRead()
{
	while (swSerial->available())
		swSerial->read();
}


int UserInterface::isCalled()
{
	return swSerial->available();
}