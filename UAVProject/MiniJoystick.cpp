// 
// 
// 

#include "MiniJoystick.h"

MiniJoystick::MiniJoystick(char* name, size_t legX, size_t legY, size_t button)
{
	this->name = name;
	this->x.leg = legX;
	this->y.leg = legY;
	this->button = button;
	pinMode(button, INPUT);
	this->x.min = 1000;
	this->y.min = 1000;
	this->x.max = -1000;
	this->y.max = -1000;
	this->y.mid = 0;
	this->x.mid = 0;
}

bool MiniJoystick::init(){
	
	Serial.print("\nplaese don't tuch the joystic for secund");
	x.mid = int(analogRead(x.leg));
	y.mid = int(analogRead(y.leg));

	//ToDo: fix it, becuse this only mesure onec
	Serial.print("\nplaese move the joystic up and down for clibretion, when you finish press the joystic");
	
	//while (buttonUnpushState == digitalRead(button)) {
	updateRange(&x, int(analogRead(x.leg)));
	updateRange(&y, int(analogRead(y.leg)));
	//}
	Serial.print("\ndone!");
}

String MiniJoystick::asciiResult() {
	String result = "[";
	result += String(getX()) + ",";
	result += String(getY()) + ",";
	result += String(digitalRead(button)) + "]";
	return result;
}

String MiniJoystick::toString() {
	String result = "\n****************** MiniJoystick *******************";
	result += "\nx = " + String(getX());
	result += "\y = " + String(getY());
	result += "\nbutton = " + String(digitalRead(button));
	result += "\n****************** MiniJoystick END *******************";
	return result;
}

DynamicJsonDocument MiniJoystick::jsonResult() {
	DynamicJsonDocument json(1024);
	//json.clear();
	json["x"] = getX();
	json["y"] = getY();
	//json["botton"]= digitalRead(button);
	json.shrinkToFit();
	return json;
}

void MiniJoystick::updateRange(Axis* axis, int input) {
	if (input > axis->max) {
		axis->max = input;
	}
	if (input < axis->min) {
		axis->min = input;
	}
}

//this function is shude be deleted if map works!
byte normalize(int x, int in_min, int in_max, int out_min, int out_max) {
	if ((in_max - in_min) == 0)	 {
		return byte(127); //don't divide in 0!  //return 127 to avoid crashing the system
	}
	return byte((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

byte MiniJoystick::axisValue(Axis* axis) {
	int input = int(analogRead(axis->leg));
	
	updateRange(axis, input);
	
	if (input < axis->mid) {
		  return byte(map(input, axis->min, axis->mid, 0, 127));
		//return normalize(input, axis->min, axis->mid, 0, 127);
	}
	else {
		return byte(map(input, axis->mid, axis->max, 128, 255));
		//return normalize(input, axis->mid, axis->max, 128, 255);
	}
}

byte MiniJoystick::getX() {
	return axisValue(&x);
	/*
	if(result  < Xmid)	{	  //0->127
		int range = (Xmid - Xmin);
		return	-( 255- constrain((result / (range / 255)),0,255));
	}
	if (result > Xmid) {		 //127->254
		int range = (Xmax-Xmid);
 		return	constrain((result - Xmid) / (range / 255),0,255);
	}
	else return 0;
	*/
}

byte MiniJoystick::getY() {
	return axisValue(&y);

		   /*
	if (result < Ymid) {	  //0->127
		int range = (Ymid - Ymin);
		return	-( 255- constrain((result / (range / 255)),0,255));
	}
	if (result > Ymid) {		 //127->254

		int range = (Ymax - Ymid);
		return	constrain((result - Ymid) / (range / 255),0,255);
	}
	else return 0;
	*/
}

bool MiniJoystick::getButton() {
		return 0 == analogRead(button);
}

