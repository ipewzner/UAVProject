// 
// 
// 

#include "logic.h"


Logic::Logic(MotorArray* motors) {
	this->motors = motors;
	this->joystic1X = 0;
	this->joystic1Y = 0;
	this->joystic2X = 0;
	this->joystic2Y = 0;
}

//Make it batter
void Logic::updateJoystic(byte joy1X, byte joy1Y, byte joy2X, byte joy2Y) {
	/*
	this->joystic1X = ((joy1X >= 0) ? map(joy1X, 0, 255, 90, 180) : map(-joy1X, 0, 255, 90, 0));
	this->joystic1Y = ((joy1Y >= 0) ? map(joy1Y, 0, 255, 90, 180) : map(-joy1Y, 0, 255, 90, 0));
	this->joystic2X = ((joy2X >= 0) ? map(joy2X, 0, 255, 90, 180) : map(-joy2X, 0, 255, 90, 0));
	this->joystic2Y = ((joy2Y >= 0) ? map(joy2Y, 0, 255, 90, 180) : map(-joy2Y, 0, 255, 90, 0));
	*/		
	
	this->joystic1X = joy1X;
	this->joystic1Y = joy1Y;
	this->joystic2X = joy2X;
	this->joystic2Y = joy2Y;
	
	/*
	this->joystic1X = joy1X;
	joystic1X = joystic1X / (255 / 90);
	(joystic1X < 0) ? joystic1X *= -1 : joystic1X += 90;
	constrain(joystic1X, 0, 180);

	this->joystic1Y = joy1Y;
	joystic1Y = joystic1Y / (255 / 90);
	(joystic1Y < 0) ? joystic1Y *= -1 : joystic1Y += 90;
	constrain(joystic1Y, 0, 180);
	
	this->joystic2X = joy2X;
	this->joystic2Y = joy2Y; 
	*/
}

void Logic::updateMotors(){
	//by hand
	motors->arr[0]->move(joystic1X);
	motors->arr[1]->move(joystic1Y);
	
	//by softwera	 //להוציא את הקבוע
	for (byte i = 0; i < 5; i++){
		
		if (desireState[i] != currentState[i]) {
			//pid
		}
	}

}
