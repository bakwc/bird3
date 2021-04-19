#pragma once

#include "crsf.h"
#include "sensors.h"
#include "pid.h"

class AltitudeHolder {
public:
    AltitudeHolder(CrossfireReceiver& receiver, Sensors& sensors);
    void setup();
    void loop();
private:
    int calculateThrust();
private:
    CrossfireReceiver& receiver;
    Sensors& sensors;
    PID pid;
    int lastThrust = 0;
    int lastHeight = 0;
    int lastTarget = 0;
    double filterAcc = 0;
    unsigned long lastThrustChangeTime = 0;
    unsigned long tickNum = 0;
};
