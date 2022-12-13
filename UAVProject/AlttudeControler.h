// AlttudeControler.h

#ifndef _ALTTUDECONTROLER_h
#define _ALTTUDECONTROLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <PID_v1.h>
class AlttudeControler : public PID
{
 public:
	void init();
};


#endif

