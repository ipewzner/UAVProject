// 
// 
// 

#include "ComArray.h"


ComArray::ComArray() {
	arrSize = 0;
}

void ComArray::addCom(Communication* com) {
	if (arrSize > 0)
	{
		Communication** temp = arr;
		arr = new Communication * [arrSize + 1];
		for (size_t i = 0; i < arrSize; i++)
		{
			arr[i] = temp[i];
		}
		arr[arrSize] = com;
		arrSize++;
		delete temp;
	}
	else
	{
		arr = new Communication * [arrSize + 1];
		arr[arrSize] = com;
		arrSize++;
	}
}

bool ComArray::initAll()
{
	bool result = true;
	for (size_t i = 0; i < length(); i++)
	{
		//if (!arr[i]->init()) result = false;
	}
	return result;
}

int ComArray::length() {
	return arrSize;
}
/*
String ComArray::asciiResultAll() {
	String result = "";
	for (size_t i = 0; i < arrSize; i++)
	{
		result += arr[i]->asciiResult();
		result += " ";
	}
	return result;
}
*/

DynamicJsonDocument ComArray::jsonResultAll() {
	DynamicJsonDocument json(1024);
	for (size_t i = 0; i < arrSize; i++)
	{
		//json[arr[i]->name] = arr[i]->jsonResult();
	}
	json.shrinkToFit();
	//serializeJson(json, Serial);

	return json;
}
