//
// Created by vince on 12.09.21.
//

#include "PublishAckPacket.h"

PublishAckPacket::PublishAckPacket(RawPacket *rawPacket, long int packetId) : RawPacket(rawPacket),
                                                                                   packetId(packetId) {}

long int PublishAckPacket::getPacketId() const {
    return packetId;
}
