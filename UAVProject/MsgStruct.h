// MsgStruct.h

#ifndef _MSGSTRUCT_h
#define _MSGSTRUCT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//nrf24 msg should not exceed 32 bytes
//float 4 byte
//int 2 byte


struct JoysticMsg {	//6 byte	 
	unsigned int msgNum;
	//mini joystic
	byte x1, y1;
	bool button1;
	byte x2, y2;
	bool button2;

	/*
	void print() {
		String result = "\n\nmsgNum: " + String(msgNum) + ") ";
		result += "\nx1: " + String(x1) + ", y1: " + String(y1) + ", button1: " + String(button1);
		result += "\nx2: " + String(x2) + ", y2: " + String(y2) + ", button2: " + String(button2);
		Serial.print(result);
	}
	*/
};

struct SensorsMsg {	   //30 byte
	unsigned int msgNum;
	
	//MPU gyro
	float x, y, z, temp;
	
	//BMP
	float BMPTemp, Pressure, Altitude;
	
	/*
	void print() {
		String result = "\n\nmsgNum: " + String(msgNum) + ") ";
		result += "\nMPU:";
		result += "\ngyr: " + String(x) + ", " + String(y) + ", " + String(z);
		result += "\ntemp: " + String(temp);
		result += "\nBMP:";
		result += "\nTemp: " + String(BMPTemp) + ", Pressure: " + String(Pressure) + ", Altitude: " + String(Altitude);
		Serial.print(result);
	}
	*/
};



#endif

