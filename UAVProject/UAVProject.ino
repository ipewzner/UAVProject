/*
 Name:		UAVProject.ino
 Created:	12/8/2021 2:17:35 PM
 Author:	ipewz
*/
							 
#include <Adafruit_BMP280.h>
#include "MsgStruct.h"
#include "AlttudeControler.h"
#include "YawControl.h"
#include "logic.h"
#include <ArduinoJson.h>	
#include "Communication.h"
#include "Lora.h"
#include "MPU.h"
#include "BMP.h"
#include "MiniJoystick.h"
#include "ServoMotor.h"
#include "MotorArray.h"
#include "SensorArray.h"
#include "ComArray.h"

#if  defined(ESP_32) && defined(GUI)
#include "ControlerInterface.h"
ControlerInterface* controlerInterface;
#endif // ESP_32 && GUI


ComArray com;
SensorArray sensors;
DynamicJsonDocument json(1024);

#ifdef RC	
MotorArray motors;
Logic* logic;
#endif // RC

struct ControlerMsg {		 //Lora lib work only with struct 
	
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

struct RcMsg {
	unsigned int msgNum;
	//MPU gyro
	float x, y, z, temp;
	//BMP
	float BMPTemp, Pressure, Altitude;
	//motors

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

ControlerMsg controlerMsg;// = { 0,0,0,0,0,0,0 };
RcMsg rcMsg;// = { 0,0,0,0,0,0,0,0 };
//RcMsg rcMsg = { 0,{0,0,0},0,0,0,0 };

void RcMsgPrint(RcMsg* msg) {
	String result = "\n\nmsgNum: " + String(msg->msgNum) + ") ";
	result += "\nMPU:";
	result += "\ngyr: " + String(msg->x) + ", " + String(msg->y) + ", " + String(msg->z);
	result += "\ntemp: " + String(msg->temp);
	result += "\nBMP:";
	result += "\nTemp: " + String(msg->BMPTemp) + ", Pressure: " + String(msg->Pressure) + ", Altitude: " + String(msg->Altitude);
	Serial.print(result);
}

void ControlerMsgPrint(ControlerMsg* msg) {
	String result = "\n\nmsgNum: " + String(msg->msgNum) + ") ";
	result += "\nx1: " + String(msg->x1) + ", y1: " + String(msg->y1) + ", button1: " + String(msg->button1);
	result += "\nx2: " + String(msg->x2) + ", y2: " + String(msg->y2) + ", button2: " + String(msg->button2);
	Serial.print(result);
}


void setup() {
	
	Serial.begin(115200);

	//com = new ComArray();
	com.addCom(new Lora(LORA_PIN_RX, LORA_PIN_TX, LORA_PIN_M0, LORA_PIN_M1, LORA_PIN_AUX));

#if  defined(ESP_32) && defined(GUI)
	controlerInterface = new WebGui();
	controlerInterface->init();
#endif // ESP_32 && GUI	

#ifdef RC
	sensors.addSensor(new MPU("MPU6050", MPU_SDA_PIN, MPU_SCL_PIN));
	//sensors.addSensor(new BMP("BMP280", BMP280_ADDR));
	motors.addMotor(new ServoMotor("motor1", MOTOR1));
	motors.addMotor(new ServoMotor("motor2", MOTOR2));
	if (motors.length() != 0) motors.initAll();
	
	logic = new Logic(&motors);
#endif // RC

#ifdef TRANSCEIVER
	sensors.addSensor(new MiniJoystick("MiniJoystick1", MINI_JOY_1_X, MINI_JOY_1_Y, MINI_JOY_1_BUTTON));
	sensors.addSensor(new MiniJoystick("MiniJoystick2", MINI_JOY_2_X, MINI_JOY_2_Y, MINI_JOY_2_BUTTON));
#endif // TRANSCEIVER

	if (sensors.length() != 0) sensors.initAll();
	//com.arr[0]->reset();

}

void loop() {

#if  defined(ESP_32) && defined(GUI)
	//for webSocket
	controlerInterface->everyLoop();
#endif // ESP_32 && GUI	

//send

#ifdef RC		
	//Serial.println(sensors.arr[0]->toString());
	rcMsg.msgNum++;

	//mpu		
	
	/*float* ypr =(((MPU*)(sensors.arr[0]))->get_ypr());
	Serial.print("\n!!rcMsg.gyr.z " + String(ypr[2] * 180 / M_PI));

	rcMsg.gyr.x = (ypr[0] * 180 )/ M_PI;
	rcMsg.gyr.y = (ypr[1] * 180 )/ M_PI;
	rcMsg.gyr.z = (ypr[2] * 180 )/ M_PI;
	Serial.print("\n@@rcMsg.gyr.z "+String(rcMsg.gyr.z));
	*/
	//rcMsg.gyr = (((MPU*)(sensors.arr[0]))->get_yprInDagree());
	float* ypr = (((MPU*)(sensors.arr[0]))->get_ypr());
	//Serial.print("\n!!rcMsg.gyr.z " + String(ypr[2] * 180 / M_PI));

	rcMsg.x =(ypr[0] * 180) / M_PI;
	rcMsg.y =(ypr[1] * 180) / M_PI;
	rcMsg.z =(ypr[2] * 180) / M_PI;
	//Serial.print("\n@@rcMsg.gyr.z " + String(rcMsg.gyr.z));
	rcMsg.temp = ((MPU*)(sensors.arr[0]))->get_temp();
	
	//bmp
	//rcMsg.BMPTemp = ((BMP*)(sensors.arr[1]))->bmp.readTemperature();
	//rcMsg.Pressure = ((BMP*)(sensors.arr[1]))->bmp.readPressure();
	//rcMsg.Altitude = ((BMP*)(sensors.arr[1]))->bmp.readAltitude(ALTITUDE_CONST);

	//bmp
	rcMsg.BMPTemp = -1.0;
	rcMsg.Pressure = -1.0;
	rcMsg.Altitude = -1.0;
	com.arr[0]->SendStruct(&rcMsg, sizeof(float) *7 + sizeof(unsigned int));// sizeof(inMsg));
	#else

	controlerMsg.msgNum++;
	controlerMsg.x1 = int(((MiniJoystick*)(sensors.arr[0]))->getX());
	controlerMsg.y1 = int(((MiniJoystick*)(sensors.arr[0]))->getY());
	controlerMsg.button1 = bool(((MiniJoystick*)(sensors.arr[0]))->getButton());
	
	controlerMsg.x2 = int(((MiniJoystick*)(sensors.arr[1]))->getX());
	controlerMsg.y2 = int(((MiniJoystick*)(sensors.arr[1]))->getY());
	controlerMsg.button2 = bool(((MiniJoystick*)(sensors.arr[1]))->getButton());
	//ControlerMsgPrint(&controlerMsg);

	com.arr[0]->SendStruct(&controlerMsg, sizeof(unsigned int) +sizeof(byte) *4 + sizeof(bool) *2);// sizeof(inMsg));
#endif // RC
	delay(100);


//receive
#ifdef RC	
	if (com.arr[0]->available()) {
		com.arr[0]->GetStruct(&controlerMsg, sizeof(unsigned int) + sizeof(byte) * 4 + sizeof(bool) * 2);
		ControlerMsgPrint(&controlerMsg);
	}
		logic->updateJoystic(controlerMsg.x1, controlerMsg.y1, controlerMsg.x2, controlerMsg.y2);
		logic->updateMotors();
	
#else
	if(com.arr[0]->available()){
		com.arr[0]->GetStruct(&rcMsg, sizeof(float) * 7 + sizeof(unsigned int));
		//com.arr[0]->GetStruct(&rcMsg, sizeof(rcMsg));
		//ToDo:try cahnge the size of to size of struct
		//rcMsg.print();
		RcMsgPrint(&rcMsg);
	}

#endif // RC
	

	delay(100);
	
	

#if  defined(ESP_32) && defined(GUI)
		//controlerInterface->show(json);
		//serializeJson(json, Serial);
#endif // ESP_32 && GUI		
		
	}
