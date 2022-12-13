#include <Adafruit_BMP280.h>

BMP::BMP(char* name, size_t i2c_address)
{
    this->name = name;
    this->i2c_address = i2c_address;
}

bool BMP::init() {

    if (!bmp.begin(i2c_address)) {
        //if (!bmp.begin()) {
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
}

String BMP::asciiResult() {
    String result = "[";
    result += String(bmp.readTemperature()) + ",";
    result += String(bmp.readPressure()) + ",";
    result += String(bmp.readAltitude(ALTITUDE_CONST)) + "]";
    return result;
}

String BMP::toString() {
    String result = "\n****************** BMP *******************";
    result += "\nTemperature = " + String(bmp.readTemperature()) + " *C";
    result += "\nPressure = " + String(bmp.readPressure()) + " Pa";
    result += "\nApprox altitude = " + String(bmp.readAltitude(ALTITUDE_CONST)) + " m";
    result += "\n****************** BMP END *******************";
    return result;
}

DynamicJsonDocument BMP::jsonResult() {

    DynamicJsonDocument json(1024);
    //json.clear();

    json["temp"] = bmp.readTemperature();
    json["pres"] = bmp.readPressure();
    json["alt"] = bmp.readAltitude(ALTITUDE_CONST);
    json.shrinkToFit();
    //serializeJson(json, Serial);

    return json;
}