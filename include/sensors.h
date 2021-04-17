#include <Wire.h>
#include <VL53L1X.h>

#include <vector>
#include <memory>

constexpr int SENSORS_START_ADDR = 0x30;
constexpr int SENSOR_START_PIN = 3;

class Sensors {
public:
    Sensors();
    void loop();
    void setup();
    int getDistance();
private:
    VL53L1X sensor;
    bool initialized = false;
    int lastDistance = -1;
};
