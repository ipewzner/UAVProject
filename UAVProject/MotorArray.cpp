#include "Motor.h"

#include "MotorArray.h"

MotorArray::MotorArray() {
	arrSize = 0;
}

size_t MotorArray::length() {
	return arrSize;
}


void MotorArray::addMotor(Motor* motor)
{
	if (arrSize > 0)
	{

		Motor** temp = arr;
		arr = new Motor * [arrSize + 1];
		for (size_t i = 0; i < arrSize; i++)
		{
			arr[i] = temp[i];
		}
		arr[arrSize] = motor;
		arrSize++;
		delete temp;
	}
	else
	{
		arr = new Motor * [arrSize + 1];
		arr[arrSize] = motor;
		arrSize++;
	}
}

bool MotorArray::initAll()
{
	bool result = true;
	for (size_t i = 0; i < length(); i++)
	{
		if (!arr[i]->init()) result = false;
	}
	return result;
}


String MotorArray::asciiResultAll() {
	String result = "";
	for (size_t i = 0; i < arrSize; i++)
	{
	//	result += arr[i]->asciiResult();
		result += " ";
	}
	return result;
}

DynamicJsonDocument MotorArray::jsonResultAll() {
	DynamicJsonDocument json(arrSize);
	for (size_t i = 0; i < arrSize; i++)
	{
		//json[arr[i]->name] = 
		//arr[i]->jsonResult();
	}
	return json;
}


