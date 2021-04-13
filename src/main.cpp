#include <Arduino.h>

#include "csrf.h"

CrossfireReceiver receiver;
unsigned long lastDebug = 0;

void setup() {
    receiver.setup();
    Serial.begin(9600);
}

void loop() {
    receiver.loop();
    auto currTime = millis();
    if (currTime - lastDebug > 50) {
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
