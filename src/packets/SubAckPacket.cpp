//
// Created by vince on 11.08.21.
//

#include "SubAckPacket.h"

SubAckPacket::SubAckPacket(RawPacket *rawPacket, unsigned short packetId, unsigned char retCode) : RawPacket(rawPacket),
                                                                                                   _packetId(packetId),
                                                                                                   _retCode(retCode) {}

unsigned short SubAckPacket::getPacketId() const {
    return _packetId;
}

unsigned char SubAckPacket::getRetCode() const {
    return _retCode;
}
