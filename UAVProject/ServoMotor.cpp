// 
// 
// 

#include "ServoMotor.h"

bool ServoMotor::init(){
	Serial.print("\nServoMotor.init start");
	this->servoNum = motorNumber(); //motorNumber is static define in Motor class needed for servo channel
	
	Serial.print("\nservoNum  ");
	Serial.print(servoNum);

	return servo.attach(signelPin, servoNum, min, max);

	//return servo.attach(signelPin);
}

ServoMotor::ServoMotor(char* name, size_t signelPin, size_t min, size_t max) {
	
	this->name = name;
	this->signelPin = signelPin;
	this->min = min;
	this->max = max;
}

void ServoMotor::move(byte deg){
	servo.write(constrain(deg, min, max));
	/*
	if (deg < min)	 deg == min;
	if (deg > max)	 deg == max;
	servo.write(deg);
	*/
}

int ServoMotor::get_currentPosition() {
	return servo.read();
}
