#include <Arduino.h>

#include <VL53L1X.h>

#include "csrf.h"
#include "sensors.h"

CrossfireReceiver receiver(Serial1);
Sensors sensors;

unsigned long lastDebug = 0;

unsigned long readFromSerial1 = 0;
unsigned long readFromSerial2 = 0;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(400000); // use 400 kHz I2C

    receiver.setup();
    receiver.setRedirectSerial(&Serial2);

    sensors.setup();

//    Serial1.begin(420000);
//    Serial2.begin(420000);
}

void loop() {
    receiver.loop();
    sensors.loop();

    auto currTime = millis();

//    while (Serial1.available()) {
//        Serial2.write(Serial1.read());
//        ++readFromSerial1;
//    }
//    while (Serial2.available()) {
//        Serial1.write(Serial2.read());
//        ++readFromSerial2;
//    }

    if (currTime - lastDebug > 1000) {
//        Serial.print("Read from serial1: ");
//        Serial.println(readFromSerial1);
//        Serial.print("Read from serial2: ");
//        Serial.println(readFromSerial2);
//        Serial.println();
//        Serial.println("Info:");
//        Serial.println(receiver.totalBytesReceived);
//        Serial.println(receiver.lastBufferSize);
//        Serial.print("Parsed: ");
//        Serial.println(receiver.successParse);
//        Serial.print("Frame len: ");
//        Serial.println(receiver.lastFrameLen);
//        Serial.println("");
//        for (int i = 0; i < 5; ++i) {
//            Serial.print("Channel ");
//            Serial.print(i);
//            Serial.print(" = ");
//            Serial.println(receiver.getChannel(i));
//        }
        for (int i = 0; i < 16; ++i) {
            Serial.print("c");
            Serial.print(i);
            Serial.print(":");
            Serial.print(receiver.getChannel(i));
            Serial.print("; ");
        }
        Serial.println();
        lastDebug = currTime;
    }
// write your code here
}
