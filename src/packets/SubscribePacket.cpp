//
// Created by derdoc on 7/4/21.
//

#include "RawPacket.h"
#include "SubscribePacket.h"


//SubscribePacket::~SubscribePacket() {
//    delete _packetId;
//    delete topicLength;
//    delete topic;
//    delete qos:
//}

//SubscribePacket::SubscribePacket(RawPacket *rawPacket, unsigned short _packetId, unsigned short topicLength, char *topic,
//                                 unsigned short qos) : RawPacket(rawPacket), _packetId(_packetId), topicLength(topicLength),
//                                                       topic(topic), qos(qos) {}


SubscribePacket::~SubscribePacket() {
    delete topic;
}

unsigned short SubscribePacket::getPacketId() const {
    return _packetId;
}

char *SubscribePacket::getTopic() const {
    return topic;
}

unsigned short SubscribePacket::getQos() const {
    return qos;
}

SubscribePacket::SubscribePacket(RawPacket *rawPacket, unsigned short packetId, char *topic, unsigned short qos)
        : RawPacket(rawPacket), _packetId(packetId), topic(topic), qos(qos) {}

