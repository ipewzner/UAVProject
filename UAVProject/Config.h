// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#define RC
//#define TRANSCEIVER
//#define GUI

#define WIFI_SSID  "ESP_TEST"
#define WIFI_PASSWORD  "yourPassword"
#define WIFI_LOCAL "esp32"		  //mDNS 

#define SPACE " "

#define MPU9250_ADDR 0x68
#define BMP280_ADDR	0x76

#define MSG_BUF_SIZE 250
#define LORA_SERIAL_SPEED 9600
#define ALTITUDE_CONST 1013.25
#define SENSOR_NAME_SIZE 10

#define ESP_32NEW
//#define ESP_32	 //doit esp32 devkit v1
//#define ESP_8266
//#define TTGO
//#define MEGA 
//#define MINI 

/*
#ifdef RC

#define SERVO1 1
#define SERVO2 2
#define SERVO3 3
#define ESC0   4
#include <Servo.h>
#endif // RC           */

#ifdef TTGO

#define MPU_SDA_PIN	21
#define MPU_SCL_PIN	22
#define LORA_PIN_M0 12
#define LORA_PIN_M1 13
#define LORA_PIN_RX 2
#define LORA_PIN_TX 15
#define LORA_PIN_AUX NULL
#endif // TTGO

#ifdef MEGA
#define LORA_PIN_M0 7
#define LORA_PIN_M1 6
#define LORA_PIN_RX 15
#define LORA_PIN_TX 14
#define LORA_PIN_AUX NULL
#endif // MEGA

#ifdef MINI
#define LORA_PIN_M0 5
#define LORA_PIN_M1 4
#define LORA_PIN_RX 3
#define LORA_PIN_TX 2
#define LORA_PIN_AUX NULL
#endif // MINI

#ifdef ESP_32
#define MPU_SDA_PIN	21
#define MPU_SCL_PIN	22
#define LORA_PIN_M0 27
#define LORA_PIN_M1 26
#define LORA_PIN_RX 33
#define LORA_PIN_TX 25
#define LORA_PIN_AUX 36
#endif // ESP_32

#ifdef ESP_32NEW
#define MPU_SDA_PIN	21
#define MPU_SCL_PIN	22

#define LORA_PIN_M0 27
#define LORA_PIN_M1 26
#define LORA_PIN_RX 33
#define LORA_PIN_TX 25
#define LORA_PIN_AUX 36

#define MOTOR1 15
#define MOTOR2 2
#define MOTOR3 0
#define MOTOR4 4
#define MOTOR5 16

//#define GPS_PPS 17
//#define GPS_RX 18	 
//#define GPS_TX 19	   
#endif // ESP_32

#ifdef ESP_8266
#define MPU_SDA_PIN	4
#define MPU_SCL_PIN	6
#define LORA_PIN_M0 10
#define LORA_PIN_M1 9
#define LORA_PIN_RX 8
#define LORA_PIN_TX 11
#define LORA_PIN_AUX NULL
#endif // ESP_8266

#define MINI_JOY_1_X	15
#define MINI_JOY_1_Y	2
#define MINI_JOY_1_BUTTON	0//17
#define MINI_JOY_2_X	4//0
#define MINI_JOY_2_Y	16//4
#define MINI_JOY_2_BUTTON	17//16
#endif
