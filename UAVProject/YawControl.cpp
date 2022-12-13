// 
// 
// 

#include "YawControl.h"

YawControl::YawControl(
	double* input,
	double* output,
	double* setpoint,
	double kp,
	double ki,
	double kd,
	int pOn,
	int controllerDirection
) {
	  	pid=new PID(input, output, setpoint, kp, ki, kd, pOn, controllerDirection);

		double* Input, * Output, * Setpoint, Kp, Ki, Kd;
	//	int POn, ControllerDirection;
		this->desireAngle = desireAngle;
		this->currentAngle= currentAngle;
		this->input = input;
		this->output = output;
		this->setpoint = setpoint;
		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
		this->pOn = pOn;
		//this->ControllerDirection = ControllerDirection;
}

void YawControl::init(){

}

bool YawControl::Compute() {
	return pid->Compute();
}
