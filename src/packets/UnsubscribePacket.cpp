//
// Created by archdoc on 10/09/2021.
//

#include "UnsubscribePacket.h"

UnsubscribePacket::~UnsubscribePacket() {
    delete topic;
}

int UnsubscribePacket::getPacketId() const {
    return _packetId;
}

char *UnsubscribePacket::getTopic() const {
    return topic;
}

UnsubscribePacket::UnsubscribePacket(RawPacket *rawPacket, int packetId, char *topic)
: RawPacket(rawPacket), _packetId(packetId), topic(topic) {}