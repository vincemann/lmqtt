//
// Created by derdoc on 7/4/21.
//

#include "RawPacket.h"
#include "SubscribePacket.h"




SubscribePacket::~SubscribePacket() {
    delete topic;
}

unsigned short SubscribePacket::getPacketId() const {
    return _packetId;
}

char *SubscribePacket::getTopic() const {
    return topic;
}

unsigned char SubscribePacket::getQos() const {
    return qos;
}

SubscribePacket::SubscribePacket(RawPacket *rawPacket, unsigned short packetId, char *topic, unsigned char qos)
        : RawPacket(rawPacket), _packetId(packetId), topic(topic), qos(qos) {}

