//
// Created by vince on 02.09.21.
//

#include <SubscribeAckPacket.h>
#include "SubscribeAckPacketParser.h"



RawPacket *SubscribeAckPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();
    unsigned short packetId;
    memcpy(&packetId,data,2);
    unsigned char retCode;
    memcpy(&retCode,data+sizeof(unsigned short),1);
    return new SubscribeAckPacket(raw_packet, packetId, retCode);
}
