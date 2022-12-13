// YawControl.h

#ifndef _YAWCONTROL_h
#define _YAWCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <PID_v1.h>

class YawControl	   
{
 public:
	 
	 double* input, * output, * setpoint, kp, ki, kd;
	 int pOn, controllerDirection;
	 float desireAngle, currentAngle;

	 YawControl(
		 double* input,
		 double* output,
		 double* setpoint,
		 double kp,
		 double ki,
		 double kd,
		 int pOn,
		 int controllerDirection
	 );
	
		 
	 PID* pid;

	bool Compute();	//it should be called every time loop() cycles

	void init();
};
#endif

