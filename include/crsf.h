#pragma once

#include <vector>

#include "Arduino.h"

class CrossfireReceiver {
public:
    CrossfireReceiver(HardwareSerial& serial);
    void loop();
    void setup();
    void setRedirectSerial(HardwareSerial* redirectSerial);
    int32_t getChannel(int channelID);
    void setChannelOverride(int channelID, int32_t newValue); // -1 to disable override
private:
    void tryParseBuffer();
    void retranslateBuffer();
public:
    int lastBufferSize = 0;
    long totalBytesReceived = 0;
    int successParse = 0;
    int lastFrameLen = 0;
private:
    std::vector<unsigned char> buffer;
    std::vector<int32_t> channels;
    std::vector<int32_t> channelOverrides;
    unsigned long lastReceiveTime = 0; // microseconds
    HardwareSerial& serial;
    HardwareSerial* serialRedirect = nullptr;
};
