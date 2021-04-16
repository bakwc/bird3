#include <vector>

class CrossfireReceiver {
public:
    CrossfireReceiver(HardwareSerial& serial);
    void loop();
    void setup();
    void setRedirectSerial(HardwareSerial* redirectSerial);
    uint32_t getChannel(int channelID);
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
    std::vector<uint32_t> channels;
    unsigned long lastReceiveTime = 0; // microseconds
    HardwareSerial& serial;
    HardwareSerial* serialRedirect = nullptr;
};
