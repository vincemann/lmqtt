//
// Created by vince on 10.09.21.
//

#include "PublishPacket.h"

PublishPacket::PublishPacket(RawPacket *rawPacket, unsigned char dupFlag, unsigned short qos,
                             unsigned char retainFlag, char *topic, unsigned short packetId, char *msg) : RawPacket(rawPacket), dupFlag(dupFlag),
                                                                 qos(qos), retainFlag(retainFlag),
                                                                 topic(topic), packetId(packetId),
                                                                 msg(msg) {}

unsigned char PublishPacket::getDupFlag() const {
    return dupFlag;
}

unsigned short PublishPacket::getQos() const {
    return qos;
}

unsigned char PublishPacket::getRetainFlag() const {
    return retainFlag;
}

char *PublishPacket::getTopic() const {
    return topic;
}

unsigned short PublishPacket::getPacketId() const {
    return packetId;
}

char *PublishPacket::getMsg() const {
    return msg;
}
