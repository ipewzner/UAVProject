// Communication.h

#ifndef _COMMUNICATION_h
#define _COMMUNICATION_h
#include <ArduinoJson.h>


class Communication
{
public:
	//virtual void send();
	//virtual void recive();
	virtual void SendStruct(const void*, uint16_t) = 0;
	virtual void GetStruct(const void*, uint16_t) = 0;
	virtual bool available() = 0;
	//virtual void SendMsg(String ) = 0;
	//virtual String GetMsg() = 0;
	virtual void flush() = 0;
	virtual void reset() = 0;
};


#endif

