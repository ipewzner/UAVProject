// MotorArray.h

#ifndef _MOTORARRAY_h
#define _MOTORARRAY_h
#include "Motor.h"

class MotorArray
{
public:
	Motor** arr;
	size_t arrSize;
	void addMotor(Motor* motor);
	bool initAll();
	MotorArray();
	size_t length();
	String asciiResultAll();
	DynamicJsonDocument jsonResultAll();
};
#endif

