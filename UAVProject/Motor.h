// Motor.h

#include <WString.h>
#include <ArduinoJson.h>
#include "Config.h"

#ifndef _MOTOR_h
#define _MOTOR_h

class Motor
{
public:
	static int motorNumber()	//needed for servo channel
	{
		static int motorNumber = 1;
		return 	  motorNumber++;
	}
		char* name;
	virtual bool init() = 0;
	virtual void move(byte) = 0;
	//virtual String asciiResult() = 0;
	//virtual DynamicJsonDocument jsonResult() = 0;
};


#endif

