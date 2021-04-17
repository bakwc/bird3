#include "sensors.h"

#include <Arduino.h>

Sensors::Sensors()
{
}

void Sensors::setup() {
    sensor.setTimeout(300);
    initialized = sensor.init();
    if (initialized) {
        sensor.setDistanceMode(VL53L1X::Long);
        sensor.setMeasurementTimingBudget(50000);
        sensor.startContinuous(50);
    }
}

void Sensors::loop() {
    if (!initialized) {
        lastDistance = -1;
        return;
    }
    if (sensor.dataReady()) {
        lastDistance = sensor.read(false);
//        Serial.print("dist:");
//        Serial.print((float)lastDistance);
//        Serial.println();
    }
}

int Sensors::getDistance() {
    return lastDistance;
}