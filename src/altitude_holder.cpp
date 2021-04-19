#include "altitude_holder.h"

#include "Arduino.h"

constexpr int CHANNEL_THRUST = 2;
constexpr int CHANNEL_ALTHOLD = 11;
constexpr int THRUST_CHANGE_PERIOD = 20; // ms
constexpr int TARGET_HEIGHT = 250;
constexpr int MIN_THRUST = 172;
constexpr int MAX_THRUST = 800;

constexpr int MAX_TARGET_CHANGE = 4;


AltitudeHolder::AltitudeHolder(CrossfireReceiver& receiver, Sensors& sensors)
    : receiver(receiver)
    , sensors(sensors)
    //, pid(0.01, MAX_THRUST, MIN_THRUST, 2.0, 0.3, 2.0)
    , pid(0.01, MAX_THRUST, MIN_THRUST, 0.8, 0.1, 1.8)
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
        lastTarget = 0;
        pid.reset();
        filterAcc = sensors.getDistance();
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

    double rawValue = sensors.getDistance();
    //constexpr double alpha = 0.6;
    constexpr double alpha = 0.5;
    filterAcc = (alpha * rawValue) + (1.0 - alpha) * filterAcc;

    int currTargetHeight = receiver.getChannel(10) + 30 - 172;
    if (currTargetHeight > lastTarget) {
        lastTarget += MAX_TARGET_CHANGE;
        lastTarget = min(currTargetHeight, lastTarget);
    }
    if (currTargetHeight < lastTarget) {
        lastTarget -= MAX_TARGET_CHANGE;
        lastTarget = max(currTargetHeight, lastTarget);
    }

    lastThrust = (int)pid.calculate(lastTarget, (double)filterAcc);
//    Serial.println(filterAcc);

    if (tickNum % 10 == 0 ) {
        Serial.print("Target Height: ");
        Serial.println(lastTarget);

        Serial.print("Filtered Height: ");
        Serial.println(filterAcc);

        Serial.print("Thrust: ");
        Serial.println(lastThrust);
        Serial.println();
    }

    if (lastTarget < 35) {
        if (filterAcc < 50.0) {
            lastThrust = 172.0;
            pid.reset();
        }
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
