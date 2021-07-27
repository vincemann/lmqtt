//
// Created by derdoc on 7/4/21.
//

#include "SubscribePacketParser.h"
#include "exception/PacketParsingException.h"
#include <stdio.h>
#include <string.h>

RawPacket *SubscribePacketParser::parse(RawPacket *rawPacket) {
    if (rawPacket->getSpecificFlags() != 2) {
        // all specific flags must be 2
        throw PacketParsingException("invalid specific flags");
    }

    unsigned char *data = rawPacket->getData();
    unsigned short packetId;
    memcpy(&packetId, data, sizeof(unsigned short));
    data += sizeof(unsigned short);

    printf("_packetId:%d\n", packetId);
//    unsigned short topicLength;
//
//    memcpy(&topicLength, data, sizeof(unsigned short));
//    data += sizeof(unsigned short);
//    Payload* topic = extractUtf8Payload(data);

    char *topic = extractUtf8Payload(&data, true);
    printf("topic:%s\n", topic);

//    unsigned short qosOffset = 2+2+topicLength;

    unsigned char qos;
    memcpy(&qos, data, sizeof(unsigned char ));

    return new SubscribePacket(rawPacket, packetId, topic, qos);
}
