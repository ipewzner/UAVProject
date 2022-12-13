// ComArray.h

#ifndef _COMARRAY_h
#define _COMARRAY_h
#include "Communication.h"

class ComArray
{
public:
	Communication** arr;
	size_t arrSize;
	void addCom(Communication* com);
	bool initAll();
	ComArray();
	int length();				//TO_DO
	String asciiResultAll();
	DynamicJsonDocument jsonResultAll();

};
#endif


