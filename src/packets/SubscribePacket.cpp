//
// Created by derdoc on 7/4/21.
//

#include "RawPacket.h"
#include "SubscribePacket.h"




SubscribePacket::~SubscribePacket() {
    delete topic;
}

int SubscribePacket::getPacketId() const {
    return _packetId;
}

char *SubscribePacket::getTopic() const {
    return topic;
}

unsigned char SubscribePacket::getQos() const {
    return qos;
}

SubscribePacket::SubscribePacket(RawPacket *rawPacket, int packetId, char *topic, unsigned char qos)
        : RawPacket(rawPacket), _packetId(packetId), topic(topic), qos(qos) {}

