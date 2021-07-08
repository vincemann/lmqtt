//
// Created by derdoc on 7/4/21.
//

#include "RawPacket.h"
#include "SubscribePacket.h"


//SubscribePacket::~SubscribePacket() {
//    delete packetId;
//    delete topicLength;
//    delete topic;
//    delete qos:
//}

//SubscribePacket::SubscribePacket(RawPacket *rawPacket, unsigned short packetId, unsigned short topicLength, char *topic,
//                                 unsigned short qos) : RawPacket(rawPacket), packetId(packetId), topicLength(topicLength),
//                                                       topic(topic), qos(qos) {}


SubscribePacket::~SubscribePacket() {
    delete topic;
}

SubscribePacket::SubscribePacket(RawPacket *rawPacket, unsigned short packetId, unsigned short topicLength, char *topic,
                                 unsigned char qos) : RawPacket(rawPacket), packetId(packetId),
                                                       topicLength(topicLength), topic(topic), qos(qos) {}

unsigned short SubscribePacket::getPacketId() const {
    return packetId;
}

unsigned short SubscribePacket::getTopicLength() const {
    return topicLength;
}

char *SubscribePacket::getTopic() const {
    return topic;
}

unsigned short SubscribePacket::getQos() const {
    return qos;
}

