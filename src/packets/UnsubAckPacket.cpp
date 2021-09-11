//
// Created by archdoc on 10/09/2021.
//

#include "UnsubAckPacket.h"

UnsubAckPacket::UnsubAckPacket(RawPacket *rawPacket, unsigned short packetId) : RawPacket(rawPacket),
                                                                                _packetId(packetId){}

unsigned short UnsubAckPacket::getPacketId() const {
    return _packetId;
}
