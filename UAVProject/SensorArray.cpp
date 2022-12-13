#include "SensorArray.h"

SensorArray::SensorArray() {
	arrSize = 0;
}

void SensorArray::addSensor(Sensor* sensor)
{
	if (arrSize > 0){
		Sensor** temp = arr;
		arr = new Sensor * [arrSize + 1];
		for (size_t i = 0; i < arrSize; i++){
			arr[i] = temp[i];
		}
		arr[arrSize] = sensor;
		arrSize++;
		delete temp;
	}
	else{
		arr = new Sensor * [arrSize + 1];
		arr[arrSize] = sensor;
		arrSize++;
	}
}

bool SensorArray::initAll()
{
	bool result = true;
	for (size_t i = 0; i < length(); i++){
		if (!arr[i]->init()) result = false;
	}
	return result;
}

int SensorArray::length() {
	return arrSize;
}

String SensorArray::asciiResultAll() {
	String result = "";
	for (size_t i = 0; i < arrSize; i++){
		result += arr[i]->asciiResult();
		result += " ";
	}
	return result;
}

DynamicJsonDocument SensorArray::jsonResultAll() {
	DynamicJsonDocument json(1024);
	//json.clear();
	
	for (size_t i = 0; i < arrSize; i++){
		json[arr[i]->name] = arr[i]->jsonResult();
	}
	//Serial.print("\nsss\n");
	//serializeJson(json,Serial);

	json.shrinkToFit();
	//serializeJson(json, Serial);

	return json;
}
