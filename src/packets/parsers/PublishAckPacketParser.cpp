//
// Created by vince on 13.10.21.
//

#include <PublishAckPacket.h>
#include "PublishAckPacketParser.h"

RawPacket *PublishAckPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();
    int packetId = 0;
    memcpy(&packetId,data, sizeof(int));
    printf("packetId: %d\n",packetId);
    return new PublishAckPacket(raw_packet,packetId);
}
