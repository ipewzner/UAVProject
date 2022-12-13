// logic.h

#ifndef _LOGIC_h
#define _LOGIC_h

#include "MotorArray.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Logic
{
 public:
	 Logic(MotorArray* motors);
	 float* ypr;
	 byte joystic1X, joystic1Y;
	 byte joystic2X, joystic2Y;
	 MotorArray* motors;

	 //לשנות לפוינטר ולהוציא את הקבוע לקובץ קונפיג
	 float desireState[5], currentState[5];//yaw, pitch, roll, speed, alt

	 void updateJoystic(byte joy1X, byte joy1Y, byte joy2X, byte joy2Y);
	 void updateMotors();

};
#endif

