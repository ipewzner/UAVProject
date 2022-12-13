// MPU.h



#ifndef _MPU_h
#define _MPU_h

#include "Sensor.h"
#include <MPU6050_6Axis_MotionApps20.h>
  
struct xyzFloat {
    float x, y, z;
};  

class MPU :public Sensor
{

    size_t sda, scl;
    // MPU control/status vars
    bool dmpReady = false;  // set true if DMP init was successful
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer

    // orientation/motion vars
    Quaternion* q;           // [w, x, y, z]         quaternion container
    VectorInt16* aa;         // [x, y, z]            accel sensor measurements
    VectorInt16* gy;         // [x, y, z]            gyro sensor measurements
    VectorInt16* aaReal;     // [x, y, z]            gravity-free accel sensor measurements
    VectorInt16* aaWorld;    // [x, y, z]            world-frame accel sensor measurements
    VectorFloat* gravity;    // [x, y, z]            gravity vector
    float euler[3];         // [psi, theta, phi]    Euler angle container
    float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    int offset[3];
public:
    
    MPU6050* mpu;

    MPU(char* name, size_t sda, size_t scl);
    bool init();
    String asciiResult();
    String toString();
    DynamicJsonDocument jsonResult();

    float* get_ypr();
    xyzFloat get_yprInDagree();
    float get_temp();

    void resetAxis(size_t axis);

};
#endif
