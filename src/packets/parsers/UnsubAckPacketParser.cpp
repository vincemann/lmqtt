//
// Created by archdoc on 10/09/2021.
//

#include <UnsubAckPacket.h>
#include "UnsubAckPacketParser.h"

RawPacket *UnsubAckPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();
    unsigned short packetId;
    memcpy(&packetId,data,2);
    return new UnsubAckPacket(raw_packet, packetId);
}
