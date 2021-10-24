//
// Created by vince on 02.09.21.
//

#include <SubscribeAckPacket.h>
#include "SubscribeAckPacketParser.h"



RawPacket *SubscribeAckPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();

    int packetId;
    memcpy(&packetId,data,sizeof(int));
    data = data + sizeof(int);

    unsigned char retCode;
    memcpy(&retCode,data,sizeof(unsigned char));

    return new SubscribeAckPacket(raw_packet, packetId, retCode);
}
