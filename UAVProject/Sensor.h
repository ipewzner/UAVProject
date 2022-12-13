// Sensor.h
#include <WString.h>
#include <ArduinoJson.h>
#include "Config.h"

#ifndef _SENSOR_h
#define _SENSOR_h

class Sensor
{
public:
	char* name;
	virtual bool init() = 0;
	virtual String asciiResult() = 0;
	virtual DynamicJsonDocument jsonResult() = 0;
	virtual String toString();
};

#endif

