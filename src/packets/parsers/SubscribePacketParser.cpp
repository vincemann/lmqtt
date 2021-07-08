//
// Created by derdoc on 7/4/21.
//
// NOT APPROVED

#include "SubscribePacketParser.h"
#include "exception/PacketParsingException.h"
#include <stdio.h>
#include <string.h>

RawPacket *SubscribePacketParser::parse(RawPacket *pRawPacket) {
    if (pRawPacket->getSpecificFlags() != 8) {
        // all specific flags must be 0
        throw PacketParsingException("invalid specific flags");
    }

    unsigned char *data = pRawPacket->getData();
//    todo: packetId "database"
    unsigned short packetId;
    memcpy(&packetId, &data, sizeof(unsigned short));
    printf("packetId:%d\n", packetId);

    unsigned short topicLength;
    memcpy(&topicLength, &data + 2, sizeof(unsigned short));

    char *topic = extractUtf8Payload(&data + 2, false);
    printf("topic:%s\n", topic);

    unsigned short qosOffset = 2+2+topicLength;
    unsigned char qos = data[qosOffset];
    if (qos > 3){
        throw PacketParsingException("invalid QoS field");
    }

    return new SubscribePacket(pRawPacket, packetId, topicLength, topic, qos);
}
