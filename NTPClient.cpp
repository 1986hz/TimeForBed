// 
// getDataTime()은 WizFi310의 예제를 참고하였습니다.
// 

#include "NTPClient.h"


void NTPClientClass::init(WizFi310Class *wifi)
{
	_wifi = wifi;
}


int NTPClientClass::getDateTime(DateTime *dateTime)
{
	if (_wifi->status() != WL_CONNECTED)
		return 0;

	int status = WL_IDLE_STATUS;
	char timeServer[] = "time.nist.gov";
	unsigned int localPort = 123;
	const int NTP_PACKET_SIZE = 48;
	byte packetBuffer[NTP_PACKET_SIZE];
	WiFiUDP Udp;
	Udp.begin(localPort);


	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	packetBuffer[0] = 0b11100011;
	packetBuffer[1] = 0;
	packetBuffer[2] = 6;
	packetBuffer[3] = 0xEC;
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	Udp.beginPacket(timeServer, 123);
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	Udp.endPacket();

	if (Udp.parsePacket()) {
		int aa = Udp.read(packetBuffer, NTP_PACKET_SIZE);

		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		const unsigned long seventyYears = 2208988800UL;
		unsigned long epoch = secsSince1900 - seventyYears;

		int hour = ((epoch % 86400L) / 3600) + 9;
		int min = (epoch % 3600) / 60;
		int sec = epoch % 60;

		if (hour == 24) hour = 0;

		dateTime->setDateTime(hour, min, sec);

		return 1;
	}

	return 0;
}


NTPClientClass NTPClient;