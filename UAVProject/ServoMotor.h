// ServoMotor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h
#include <Servo_ESP32.h>
#include "Motor.h"
class ServoMotor :public Motor
{
public:
    Servo_ESP32 servo;
	size_t signelPin, min, max;
	int servoNum;
	ServoMotor(char* name,size_t signelPin, size_t min=0, size_t max =180);
	bool init();
	void move(byte deg);
	int get_currentPosition(); 
	

};
#endif

    
