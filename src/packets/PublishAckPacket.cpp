//
// Created by vince on 12.09.21.
//

#include "PublishAckPacket.h"

PublishAckPacket::PublishAckPacket(RawPacket *rawPacket, unsigned long packetId) : RawPacket(rawPacket),
                                                                                   packetId(packetId) {}

unsigned long PublishAckPacket::getPacketId() const {
    return packetId;
}
