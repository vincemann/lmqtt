//
// Created by archdoc on 10/09/2021.
//

#include <UnsubscribePacket.h>
#include "UnsubscribePacketParser.h"

RawPacket *UnsubscribePacketParser::parse(RawPacket *raw_packet) {
    unsigned char *data = raw_packet->getData();
    unsigned short packetId;
    memcpy(&packetId, data, sizeof(unsigned short));
    data += sizeof(unsigned short);
    char *topic = extractUtf8Payload(&data, true);
    return new UnsubscribePacket(raw_packet, packetId, topic);
}

