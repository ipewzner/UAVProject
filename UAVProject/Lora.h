// Lora.h
#ifndef _LORA_h
#define _LORA_h

#include "Config.h"
#include "Communication.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>	
#include "EBYTE.h"

class Lora : public Communication
{
public:
	//SoftwareSerial* loraSerial;
	HardwareSerial* 	  loraSerial;
	EBYTE* transceiver;

	Lora(int8_t rx, int8_t tx, int8_t m0, int8_t m1, int8_t aux);
	//	void begin(int speed);
	void SendStruct(const void*, uint16_t);
	bool available();
	void GetStruct(const void*, uint16_t);
	void flush();
	void reset();

};

#endif;