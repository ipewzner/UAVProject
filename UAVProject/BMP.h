// BMP.h
#undef MODE_NORMAL

#ifndef _BMP_h
#define _BMP_h

#include "Sensor.h"
#include <Adafruit_BMP280.h>

//bmp280 sense: humidity, temperature, pressure

class BMP :public Sensor
{
public:
	BMP(char* name, size_t i2c_address);
	size_t i2c_address;
	Adafruit_BMP280 bmp;
	bool init();
	String asciiResult();
	String toString();
	DynamicJsonDocument jsonResult();

};

#endif

