#include "Lora.h"

//Lora::Lora(int TX, int RX, int M0, int M1, int AUX = NULL) {
Lora::Lora(int8_t rx, int8_t tx, int8_t m0, int8_t m1, int8_t aux) {
    //pinMode(rx, INPUT);
    //pinMode(aux, INPUT);
    //pinMode(aux, INPUT_PULLUP);
    //pinMode(rx, INPUT_PULLDOWN);

    //loraSerial = new SoftwareSerial(rx, tx);
    //loraSerial->begin(115200);
    loraSerial = new HardwareSerial(1);
    loraSerial->begin(9600, SERIAL_8N1, rx, tx);

    //loraSerial->begin(LORA_SERIAL_SPEED);
    transceiver = new EBYTE(loraSerial, m0, m1, aux);
    //transceiver = new EBYTE(loraSerial, LORA_PIN_M0, LORA_PIN_M1);
    //transceiver = new EBYTE(&loraSerial, LORA_PIN_M0, LORA_PIN_M1, LORA_PIN_AUX);
    transceiver->init();

    transceiver->PrintParameters();
    Serial.print("\ntransceiver->GetUARTBaudRate() ");
    Serial.print(transceiver->GetUARTBaudRate());
    transceiver->SetUARTBaudRate(UDR_9600);
    //transceiver->SetUARTBaudRate(UDR_115200);    
    transceiver->SetAirDataRate(ADR_19200);
    transceiver->SetParityBit(0);//fix me!!!!!!!!!
    transceiver->SetAddressH(4);
    transceiver->SetAddressL(5);
    transceiver->SetChannel(1);
    transceiver->SetOptions(68);
    transceiver->SetParityBit(PB_8N1);
    //transceiver->SetTransmitPower(OPT_TP10);
    transceiver->SaveParameters(PERMANENT);
    Serial.print("\ntransceiver->GetUARTBaudRate() ");
    Serial.print(transceiver->GetUARTBaudRate());
    transceiver->PrintParameters();
   
    delay(100);
    //loraSerial->end();
    //loraSerial->begin(LORA_SERIAL_SPEED);
}
/*
void Lora::begin(int speed) {
    //loraSerial->begin(speed);
    transceiver->init();
    delay(100);


    transceiver->PrintParameters();

    transceiver->SetUARTBaudRate(UDR_9600);
    transceiver->SetAirDataRate(ADR_19200);
    transceiver->SetChannel(14);
    transceiver->SetOptions(68);
    //transceiver->SetTransmitPower(OPT_TP10);
    transceiver->SaveParameters(PERMANENT);
    delay(100);

    loraSerial->end();
    loraSerial->begin(9600);
    transceiver->PrintParameters();

}
        */
void Lora::SendStruct(const void* Struct, uint16_t size) {
    transceiver->SendStruct(Struct, size);
    //transceiver->flush();
}

void Lora::GetStruct(const void* Struct, uint16_t size) {
    transceiver->GetStruct(Struct, size);
   // transceiver->flush();
}

bool Lora::available() {
    return transceiver->available();
}

void Lora::flush() {
    transceiver->flush();
}


void Lora::reset() {
    transceiver->Reset();
}
