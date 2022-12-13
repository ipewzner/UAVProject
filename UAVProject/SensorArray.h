// SensorArray.h

#ifndef _SENSORARRAY_h
#define _SENSORARRAY_h

#include "Sensor.h"
#include "MPU.h" 
#include "BMP.h" 

class SensorArray
{
public:
	Sensor** arr;
	size_t arrSize;
	void addSensor(Sensor* sensor);
	bool initAll();
	SensorArray();
	int length();				//TO_DO
	String asciiResultAll();
	DynamicJsonDocument jsonResultAll();

};

#endif

