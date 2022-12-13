// ControlerArray.h

#ifndef _CONTROLERARRAY_h
#define _CONTROLERARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class ControlerArrayClass
{
protected:


public:
	void init();
};

extern ControlerArrayClass ControlerArray;

#endif

