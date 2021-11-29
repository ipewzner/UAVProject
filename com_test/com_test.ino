/*
 Name:		com_test.ino
 Created:	10/28/2021 1:30:53 PM
 Author:	ipewz
*/

//esp				   
#include <SoftwareSerial.h>
#include "EBYTE.h"

#define TTGO
//#define MEGA 
//#define MINI
#define RC
//#define TRANSCEIVER
/*
#ifdef RC

#define SERVO1 1
#define SERVO2 2
#define SERVO3 3
#define ESC0   4
#include <Servo.h>  
#endif // RC           */

#ifdef TTGO
#define PIN_M0 12
#define PIN_M1 13
#define PIN_RX 15
#define PIN_TX 2
#endif // TTGO

#ifdef MEGA
#define PIN_M0 7
#define PIN_M1 6
#define PIN_RX 15
#define PIN_TX 14
#endif // MEGA

#ifdef MINI
#define PIN_M0 5
#define PIN_M1 4
#define PIN_RX 3
#define PIN_TX 2
#endif // MINI

SoftwareSerial LoraSerial(PIN_TX, PIN_RX);
EBYTE Transceiver(&LoraSerial, PIN_M0, PIN_M1 ,NULL);

#ifdef RC

//bmp280 sense: humidity, temperature, pressure
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; 

//mpu sense: giro, axel, temperature
#include <MPU9250_WE.h>
#include <Wire.h>
#define MPU9250_ADDR 0x68
MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);

//Servo servo[4];
#endif // RC

struct RC_TO_TRANSCEIVER_DATA {
	//char str[1000];
	
    int msgNum;
    float Acceleration[3];
    float Gyroscope[3];
    float Magnetometer[3];
    float Temperature;

    String print() {
        String result = "\n****************** MPU *******************";
        result +="\nmsgNum: "+ String(msgNum);
        result += "\nAcceleration in g (x,y,z): \n";
        result += String(Acceleration[0]) + "   " + String(Acceleration[1]) + "   " + String(Acceleration[2]);
        result += "\nGyroscope data in degrees/s: \n";
        result += String(Gyroscope[0]) + "   " + String(Gyroscope[1]) + "   " + String(Gyroscope[2]);
        result += "\nMagnetometer Data in µTesla: \n";
        result += String(Magnetometer[0]) + "   " + String(Magnetometer[1]) + "   " + String(Magnetometer[2]);
        result += "\nTemperature in °C: " + String(Temperature);
        result += "\n**************** MPU END******************";
		return result;
	}
};
RC_TO_TRANSCEIVER_DATA rtt;

struct TRANSCEIVER_TO_RC_DATA {
	int msgNum;
	size_t motor[4];
	String print() {
		String msg = "new msg: " + String(msgNum) + ")"+"motors: "+ motor[0]+" "+ motor[1] + " " + motor[2] + " " + motor[3];
		return msg;
	}
};
TRANSCEIVER_TO_RC_DATA ttr;


void setup() {

	Serial.begin(115200);
	while (!Serial) {}
	delay(100);

#ifdef MINI
	Serial.println("MINI");
#endif // MINI
	
	LoraSerial.begin(9600);

#ifdef TTGO
	//while (!LoraSerial) {}
	Serial.println("TTGO");
#endif // TTGO

#pragma region LORA_SETUP

    Transceiver.init();
    delay(100);

    Transceiver.PrintParameters();

    Transceiver.SetUARTBaudRate(UDR_9600);
    Transceiver.SetAirDataRate(ADR_19200);
    Transceiver.SetChannel(14);
    Transceiver.SetOptions(68);
    //Transceiver.SetTransmitPower(OPT_TP10);
    Transceiver.SaveParameters(PERMANENT);
    delay(100);

    LoraSerial.end();
    LoraSerial.begin(9600);
    Transceiver.PrintParameters();

#pragma endregion

#ifdef RC
#pragma region MOTORS_SETUP
     
    /*
    servo[0].attach(SERVO1);
	servo[1].attach(SERVO2);
	servo[2].attach(SERVO3);
	servo[3].attach(ESC0);
        */

#pragma endregion

#pragma region MPU_SETUP

    Wire.begin(21, 22);
    delay(100);
    (!myMPU9250.init()) ? Serial.println("MPU9250 does not respond") : Serial.println("MPU9250 is connected");
    (!myMPU9250.initMagnetometer()) ? Serial.println("Magnetometer does not respond") : Serial.println("Magnetometer is connected");

    /* The slope of the curve of acceleration vs measured values fits quite well to the theoretical
     * values, e.g. 16384 units/g in the +/- 2g range. But the starting point, if you position the
     * MPU9250 flat, is not necessarily 0g/0g/1g for x/y/z. The autoOffset function measures offset
     * values. It assumes your MPU9250 is positioned flat with its x,y-plane. The more you deviate
     * from this, the less accurate will be your results.
     * The function also measures the offset of the gyroscope data. The gyroscope offset does not
     * depend on the positioning.
     * This function needs to be called at the beginning since it can overwrite your settings!
     */
    Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
    delay(1000);
    myMPU9250.autoOffsets();
    Serial.println("Done!");

    /*  This is a more accurate method for calibration. You have to determine the minimum and maximum
     *  raw acceleration values of the axes determined in the range +/- 2 g.
     *  You call the function as follows: setAccOffsets(xMin,xMax,yMin,yMax,zMin,zMax);
     *  Use either autoOffset or setAccOffsets, not both.
     */
     //myMPU9250.setAccOffsets(-14240.0, 18220.0, -17280.0, 15590.0, -20930.0, 12080.0);

     /*  The gyroscope data is not zero, even if you don't move the MPU9250.
      *  To start at zero, you can apply offset values. These are the gyroscope raw values you obtain
      *  using the +/- 250 degrees/s range.
      *  Use either autoOffset or setGyrOffsets, not both.
      */
      //myMPU9250.setGyrOffsets(45.0, 145.0, -105.0);

      /*  You can enable or disable the digital low pass filter (DLPF). If you disable the DLPF, you
       *  need to select the bandwdith, which can be either 8800 or 3600 Hz. 8800 Hz has a shorter delay,
       *  but higher noise level. If DLPF is disabled, the output rate is 32 kHz.
       *  MPU9250_BW_WO_DLPF_3600
       *  MPU9250_BW_WO_DLPF_8800
       */
    myMPU9250.enableGyrDLPF();
    //myMPU9250.disableGyrDLPF(MPU9250_BW_WO_DLPF_8800); // bandwdith without DLPF

    /*  Digital Low Pass Filter for the gyroscope must be enabled to choose the level.
     *  MPU9250_DPLF_0, MPU9250_DPLF_2, ...... MPU9250_DPLF_7
     *
     *  DLPF    Bandwidth [Hz]   Delay [ms]   Output Rate [kHz]
     *    0         250            0.97             8
     *    1         184            2.9              1
     *    2          92            3.9              1
     *    3          41            5.9              1
     *    4          20            9.9              1
     *    5          10           17.85             1
     *    6           5           33.48             1
     *    7        3600            0.17             8
     *
     *    You achieve lowest noise using level 6
     */
    myMPU9250.setGyrDLPF(MPU9250_DLPF_6);

    /*  Sample rate divider divides the output rate of the gyroscope and accelerometer.
     *  Sample rate = Internal sample rate / (1 + divider)
     *  It can only be applied if the corresponding DLPF is enabled and 0<DLPF<7!
     *  Divider is a number 0...255
     */
    myMPU9250.setSampleRateDivider(5);

    /*  MPU9250_GYRO_RANGE_250       250 degrees per second (default)
     *  MPU9250_GYRO_RANGE_500       500 degrees per second
     *  MPU9250_GYRO_RANGE_1000     1000 degrees per second
     *  MPU9250_GYRO_RANGE_2000     2000 degrees per second
     */
    myMPU9250.setGyrRange(MPU9250_GYRO_RANGE_250);

    /*  MPU9250_ACC_RANGE_2G      2 g   (default)
     *  MPU9250_ACC_RANGE_4G      4 g
     *  MPU9250_ACC_RANGE_8G      8 g
     *  MPU9250_ACC_RANGE_16G    16 g
     */
    myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);

    /*  Enable/disable the digital low pass filter for the accelerometer
     *  If disabled the bandwidth is 1.13 kHz, delay is 0.75 ms, output rate is 4 kHz
     */
    myMPU9250.enableAccDLPF(true);

    /*  Digital low pass filter (DLPF) for the accelerometer, if enabled
     *  MPU9250_DPLF_0, MPU9250_DPLF_2, ...... MPU9250_DPLF_7
     *   DLPF     Bandwidth [Hz]      Delay [ms]    Output rate [kHz]
     *     0           460               1.94           1
     *     1           184               5.80           1
     *     2            92               7.80           1
     *     3            41              11.80           1
     *     4            20              19.80           1
     *     5            10              35.70           1
     *     6             5              66.96           1
     *     7           460               1.94           1
     */
    myMPU9250.setAccDLPF(MPU9250_DLPF_6);

    /* You can enable or disable the axes for gyroscope and/or accelerometer measurements.
     * By default all axes are enabled. Parameters are:
     * MPU9250_ENABLE_XYZ  //all axes are enabled (default)
     * MPU9250_ENABLE_XY0  // X, Y enabled, Z disabled
     * MPU9250_ENABLE_X0Z
     * MPU9250_ENABLE_X00
     * MPU9250_ENABLE_0YZ
     * MPU9250_ENABLE_0Y0
     * MPU9250_ENABLE_00Z
     * MPU9250_ENABLE_000  // all axes disabled
     */
     //myMPU9250.enableAccAxes(MPU9250_ENABLE_XYZ);
     //myMPU9250.enableGyrAxes(MPU9250_ENABLE_XYZ);

     /*
      * AK8963_PWR_DOWN
      * AK8963_CONT_MODE_8HZ         default
      * AK8963_CONT_MODE_100HZ
      * AK8963_FUSE_ROM_ACC_MODE
      */
    myMPU9250.setMagOpMode(AK8963_CONT_MODE_100HZ);
    delay(200);

#pragma endregion

#pragma region BMP_SETUP

    //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    if (!bmp.begin()) {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
            "try a different address!"));
        while (1) delay(10);
    }

    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

#pragma endregion

   #endif // RC
}

void loop() {

	delay(10);

#ifdef TRANSCEIVER

	//send
	if (Serial.available()) {
		Transceiver.SendStruct(&ttr, sizeof(ttr));
	}

	//receive
	if (Transceiver.available()) {
		Transceiver.GetStruct(&rtt, sizeof(rtt));
		Serial.print(rtt.print());
	}

#endif // !TRANSCEIVER

#ifdef RC
		
	//send
	if (Serial.available()) {
		Transceiver.SendStruct(&rtt, sizeof(rtt));
	}

	//receive
	if (Transceiver.available()) {
		Transceiver.GetStruct(&ttr, sizeof(ttr));
		Serial.print(ttr.print());
	/*	for (size_t i = 0; i < 4; i++) {
			servo[i].write(ttr.motor[i]);
		}*/
	}

#pragma region MPU_LOOP

    //mpu
    xyzFloat gValue = myMPU9250.getGValues();
    xyzFloat gyr = myMPU9250.getGyrValues();
    xyzFloat magValue = myMPU9250.getMagValues();
    float temp = myMPU9250.getTemperature();
    float resultantG = myMPU9250.getResultantG(gValue);

    rtt.msgNum++;

    rtt.Acceleration[0] = gValue.x;
    rtt.Acceleration[1] = gValue.y;
    rtt.Acceleration[2] = gValue.z;

    rtt.Gyroscope[0] = gyr.x;
    rtt.Gyroscope[1] = gyr.y;
    rtt.Gyroscope[2] = gyr.z;

    rtt.Magnetometer[0] = magValue.x;
    rtt.Magnetometer[1] = magValue.y;
    rtt.Magnetometer[2] = magValue.z;
    rtt.Temperature = temp;

    Serial.println(rtt.print());
    Serial.println("Resultant g: " + String(resultantG));

    Transceiver.SendStruct(&rtt, sizeof(rtt));
    delay(1000);
#pragma endregion

#pragma region BMP_LOOP
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
#pragma endregion
 
#endif // !RC

}

