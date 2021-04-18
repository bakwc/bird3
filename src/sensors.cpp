#include "sensors.h"

#include <Arduino.h>

Sensors::Sensors()
{
}

void Sensors::setup() {
    sensor.setTimeout(300);
    initialized = sensor.init();
    if (initialized) {
        sensor.setDistanceMode(VL53L1X::Short);
        sensor.setMeasurementTimingBudget(10000);
        sensor.startContinuous(10);
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

int Sensors::getDistance() const {
    return lastDistance;
}

bool Sensors::isInitialized() const {
    return initialized;
}
