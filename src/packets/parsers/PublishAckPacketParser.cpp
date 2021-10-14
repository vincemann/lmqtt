//
// Created by vince on 13.10.21.
//

#include <PublishAckPacket.h>
#include "PublishAckPacketParser.h"

RawPacket *PublishAckPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();
    long int packetId = 0;
    memcpy(&packetId,data, sizeof(long int));
    printf("packetId: %ld\n",packetId);
    return new PublishAckPacket(raw_packet,packetId);
}
