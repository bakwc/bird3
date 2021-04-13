#include <Arduino.h>

#include "csrf.h"
#include "csrf_protocol.h"



CrossfireReceiver::CrossfireReceiver() {
    buffer.reserve(CRSF_FRAME_SIZE_MAX * 2);
    channels.resize(CRSF_MAX_CHANNEL);
}

uint32_t CrossfireReceiver::getChannel(int channelID) {
    if (channelID < channels.size()) {
        return channels[channelID];
    }
    return 0;
}

void CrossfireReceiver::setup() {
    Serial1.begin(CRSF_BAUDRATE);
}

void CrossfireReceiver::loop() {
    unsigned long currTime = micros();
    while (Serial1.available()) {

        long timeDelta = currTime - lastReceiveTime;
        if (timeDelta > CRSF_TIME_NEEDED_PER_FRAME_US) {
            lastBufferSize = buffer.size();
            processBuffer();
            buffer.clear();
        }

        unsigned char c = Serial1.read();
        buffer.push_back(c);
        lastReceiveTime = currTime;
        ++totalBytesReceived;
    }
}

void CrossfireReceiver::processBuffer() {
    if (buffer.size() < 5) {
        return;
    }
    crsfFrameDef_t* frame = (crsfFrameDef_t*)&buffer[0];
    lastFrameLen = frame->frameLength;
    if (buffer.size() != frame->frameLength+2) {
        return;
    }
    if (frame->type != CRSF_FRAMETYPE_RC_CHANNELS_PACKED) {
        return;
    }

    crsfPayloadRcChannelsPacked_t* rcChannels = (crsfPayloadRcChannelsPacked_t*)&frame->payload;

    channels[0] = rcChannels->chan0;
    channels[1] = rcChannels->chan1;
    channels[2] = rcChannels->chan2;
    channels[3] = rcChannels->chan3;
    channels[4] = rcChannels->chan4;
    channels[5] = rcChannels->chan5;
    channels[6] = rcChannels->chan6;
    channels[7] = rcChannels->chan7;
    channels[8] = rcChannels->chan8;
    channels[9] = rcChannels->chan9;
    channels[10] = rcChannels->chan10;
    channels[11] = rcChannels->chan11;
    channels[12] = rcChannels->chan12;
    channels[13] = rcChannels->chan13;
    channels[14] = rcChannels->chan14;
    channels[15] = rcChannels->chan15;

    ++successParse;
}
