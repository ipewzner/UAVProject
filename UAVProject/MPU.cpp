#include "mpu.h"

float MPU::get_temp() {
   // return  mpu->getTemperature();
    return (float(mpu->getTemperature() + 521) / 340 + 35.0);
}

float* MPU::get_ypr() {
    if (mpu->dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 
        mpu->dmpGetQuaternion(q, fifoBuffer);
        mpu->dmpGetGravity(gravity, q);
        mpu->dmpGetYawPitchRoll(ypr, q, gravity);
    }
    return  ypr;
}

xyzFloat MPU::get_yprInDagree() {
    get_ypr();
    xyzFloat result;
    result.x = ypr[0] * 180 / M_PI;
    result.y = ypr[1] * 180 / M_PI;
    result.z = ypr[2] * 180 / M_PI;
    return  result;
}

String MPU::toString() {
    if (mpu->dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 
        mpu->dmpGetQuaternion(q, fifoBuffer);
        mpu->dmpGetGravity(gravity, q);
        mpu->dmpGetYawPitchRoll(ypr, q, gravity);
        mpu->dmpGetAccel(aa, fifoBuffer);
        mpu->dmpGetLinearAccel(aaReal, aa, gravity);
        mpu->dmpGetLinearAccelInWorld(aaWorld, aaReal, q);
        
    }                                   
    float temp = mpu->getTemperature();
    String result = "\n****************** MPU *******************";
    
    // display real acceleration, adjusted to remove gravity
    result += "\nareal) x: "+String(aaReal->x)+ ", y: "+String(aaReal->y)+ ", z: "+String(aaReal->z);

    //result += "\nGyroscope data in degrees/s: \n";
    result +="\nypr) x:"+String(ypr[0] * 180 / M_PI) + ", y: "+String(ypr[1] * 180 / M_PI)+",z: "+String(ypr[2] * 180 / M_PI);

    // display initial world-frame acceleration, adjusted to remove gravity and rotated based on known orientation from quaternion
    result += "\naworld) x: "+String(aaWorld->x) + ", y: " + String(aaWorld->y) + ", z: " + String(aaWorld->z);

    result += "\nTemperature in °C: " + String(temp);

    result += "\n**************** MPU END******************";
    return result;
}

String MPU::asciiResult() {
    return toString();
}

void MPU::resetAxis(size_t axis) {

    switch (axis)
    {
    case 0:
        //mpu.setXGyroOffset(offset[0]);
        mpu->setXGyroOffset(0);
        break;
    case 1:
        //mpu.setYGyroOffset(offset[1]);
        mpu->setYGyroOffset(0);
        break;
    case 2:
        //mpu.setZGyroOffset(offset[2]);
        mpu->setZGyroOffset(0);
        break;
    default:
        break;
    }
}

DynamicJsonDocument MPU::jsonResult() {

    DynamicJsonDocument json(1024);
    //json.clear();
    json["g"]["x"] = aaReal->x;
    json["g"]["y"] = aaReal->y;
    json["g"]["z"] = aaReal->z;

    json["gyr"]["x"] = (ypr[0] * 180 / M_PI);
    json["gyr"]["y"] = (ypr[1] * 180 / M_PI);
    json["gyr"]["z"] = (ypr[2] * 180 / M_PI);


    json["temp"] = mpu->getTemperature();
    json.shrinkToFit();
    //serializeJson(json, Serial);

    return json;
}

MPU::MPU(char* name, size_t sda, size_t scl) {
    this->name = name;
    this->sda = sda;
    this->scl = scl;

    q = new     Quaternion();
    aa = new   VectorInt16();
    gy = new   VectorInt16();
    aaReal = new   VectorInt16();
    aaWorld = new   VectorInt16();
    gravity = new   VectorFloat();

   //this->offset[0] = offsetX;
   //this->offset[1] = offsetY;
   //this->offset[2] = offsetZ;
    Serial.println("MPU c-tor end");
}
                      
bool MPU::init() {  
    Serial.println("MPU init");

        // join I2C bus (I2Cdev library doesn't do this automatically)
        if (!Wire.availableForWrite()) {
            Wire.begin(sda, scl);
            Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
        }
                 
        this->mpu = new MPU6050();

        // initialize device
        Serial.println(F("Initializing I2C devices..."));
        mpu->initialize();

        // verify connection
        Serial.println(F("Testing device connections..."));
        Serial.println(mpu->testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

        // load and configure the DMP
        Serial.println(F("Initializing DMP..."));
        devStatus = mpu->dmpInitialize();


        // supply your own gyro offsets here, scaled for min sensitivity
        mpu->setXGyroOffset(51);
        mpu->setYGyroOffset(8);
        mpu->setZGyroOffset(21);
        mpu->setXAccelOffset(1150);
        mpu->setYAccelOffset(-50);
        mpu->setZAccelOffset(1060);
        // make sure it worked (returns 0 if so)
        if (devStatus == 0) {
            // Calibration Time: generate offsets and calibrate our MPU6050
            mpu->CalibrateAccel(6);
            mpu->CalibrateGyro(6);
            Serial.println();
            mpu->PrintActiveOffsets();
            // turn on the DMP, now that it's ready
            Serial.println(F("Enabling DMP..."));
            mpu->setDMPEnabled(true);

            // set our DMP Ready flag so the main loop() function knows it's okay to use it
            //Serial.println(F("DMP ready! Waiting for first interrupt..."));
            dmpReady = true;

            // get expected DMP packet size for later comparison
            packetSize = mpu->dmpGetFIFOPacketSize();
        }
        else {
            // ERROR!
            // 1 = initial memory load failed
            // 2 = DMP configuration updates failed
            // (if it's going to break, usually the code will be 1)
            Serial.print(F("DMP Initialization failed (code "));
            Serial.print(devStatus);
            Serial.println(F(")"));
        }
        Serial.println("MPU init end");    
}


