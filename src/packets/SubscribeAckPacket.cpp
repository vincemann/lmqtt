//
// Created by vince on 11.08.21.
//

#include "SubscribeAckPacket.h"

SubscribeAckPacket::SubscribeAckPacket(RawPacket *rawPacket, int packetId, unsigned char retCode) : RawPacket(rawPacket),
                                                                                                               _packetId(packetId),
                                                                                                               _retCode(retCode) {}

int SubscribeAckPacket::getPacketId() const {
    return _packetId;
}

unsigned char SubscribeAckPacket::getRetCode() const {
    return _retCode;
}
