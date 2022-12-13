// MiniJoystick.h

#ifndef _MINIJOYSTICK_h
#define _MINIJOYSTICK_h
#include "Sensor.h"
class MiniJoystick :public Sensor
{
public:
	MiniJoystick(char* name, size_t x, size_t y, size_t button);
	size_t button;
	
	struct Axis{
		size_t leg;
		int min, max, mid;
	};
	
	Axis x, y;
	bool buttonUnpushState;
	bool init();
	String asciiResult();
	String toString();
	DynamicJsonDocument jsonResult();
	byte getX();
	byte getY();
	bool getButton();
	byte axisValue(Axis* axis);
	void updateRange(Axis* axis, int input);
};
#endif

