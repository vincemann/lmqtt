//
// Created by vince on 12.09.21.
//

#include "PublishAckPacket.h"

PublishAckPacket::PublishAckPacket(RawPacket *rawPacket, int packetId) : RawPacket(rawPacket),
                                                                                   packetId(packetId) {}

int PublishAckPacket::getPacketId() const {
    return packetId;
}
