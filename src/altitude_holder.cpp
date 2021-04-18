#include "altitude_holder.h"

#include "Arduino.h"

constexpr int CHANNEL_THRUST = 2;
constexpr int CHANNEL_ALTHOLD = 11;
constexpr int THRUST_CHANGE_PERIOD = 20; // ms
constexpr int TARGET_HEIGHT = 130;
constexpr int MIN_THRUST = 172;
constexpr int MAX_THRUST = 750;


AltitudeHolder::AltitudeHolder(CrossfireReceiver& receiver, Sensors& sensors)
    : receiver(receiver)
    , sensors(sensors)
    , pid(0.01, MAX_THRUST, MIN_THRUST, 2.0, 0.1, 0.4)
{
}

void AltitudeHolder::setup() {
}

void AltitudeHolder::loop() {

    int32_t newThrustOverride = -1; // no override

    //newThrustOverride = calculateThrust();

    if (receiver.getChannel(CHANNEL_ALTHOLD) > 1000 && sensors.isInitialized()) {
        newThrustOverride = calculateThrust();
        //Serial.print("Curr value: ");
        //Serial.println(receiver.getChannel(CHANNEL_THRUST));
    } else {
        lastThrust = 0;
        pid.reset();
    }

    receiver.setChannelOverride(CHANNEL_THRUST, newThrustOverride);
}

int AltitudeHolder::calculateThrust() {
    unsigned long currTime = millis();
    if (currTime < lastThrustChangeTime + THRUST_CHANGE_PERIOD) {
        return lastThrust;
    }
    tickNum++;

    lastThrustChangeTime = currTime;

    int currHeight = sensors.getDistance();


    lastThrust = (int)pid.calculate(TARGET_HEIGHT, (double)currHeight);


    if (tickNum % 10 == 0) {
        Serial.print("Height: ");
        Serial.println(currHeight);

        Serial.print("Thrust: ");
        Serial.println(lastThrust);
        Serial.println();
    }

    return lastThrust;

//    if (currHeight < TARGET_HEIGHT) {
//        if (currHeight <= lastHeight) {
//            lastThrust += THRUST_CHANGE_RATE;
//        }
//    }
//
//    if (currHeight > TARGET_HEIGHT) {
//        if (currHeight >= lastHeight) {
//            lastThrust -= THRUST_CHANGE_RATE;
//        }
//    }
//
//    lastThrust = min(lastThrust, MAX_THRUST);
//    lastThrust = max(lastThrust, MIN_THRUST);
//
//    lastHeight = currHeight;
//
//    Serial.print("height: ");
//    Serial.println(lastHeight);
//
//    Serial.print("new thrust: ");
//    Serial.println(lastThrust);

//    return lastThrust;
}
