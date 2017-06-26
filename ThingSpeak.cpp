#include "ThingSpeak.h"


ThingSpeak::ThingSpeak(String apiKey)
{
	this->apiKey = apiKey;
}


void ThingSpeak::Update(String fieldValue1, String fieldValue2)
{
	if (client.connect("api.thingspeak.com", 80)) { // "184.106.153.149" or api.thingspeak.com
		String postStr = "GET /update?api_key=";
		postStr += apiKey;
		postStr += "&field1=";
		postStr += fieldValue1;
		postStr += "&field2=";
		postStr += fieldValue2;
		postStr += "\r\n\r\n";
		client.print(postStr);
	}
	client.stop();
}