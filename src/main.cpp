#include <Arduino.h>

#include "csrf.h"

CrossfireReceiver receiver(Serial1);
unsigned long lastDebug = 0;

unsigned long readFromSerial1 = 0;
unsigned long readFromSerial2 = 0;

void setup() {
    receiver.setup();
    receiver.setRedirectSerial(&Serial2);

    Serial.begin(9600);

//    Serial1.begin(420000);
//    Serial2.begin(420000);
}

void loop() {
    receiver.loop();
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
        Serial.println(receiver.getChannel(2));
        lastDebug = currTime;
    }
// write your code here
}
