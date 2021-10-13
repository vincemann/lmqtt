//
// Created by vince on 10.09.21.
//

#include <PublishPacket.h>
#include "PublishPacketParser.h"

RawPacket *PublishPacketParser::parse(RawPacket *raw_packet) {
    unsigned char* data = raw_packet->getData();

    unsigned char specificFlags = raw_packet->getSpecificFlags();
    Utils::printBits(specificFlags);

    unsigned char mask = Utils::createBitMask(3, 3);
    unsigned char dupFlag = mask & specificFlags;

    mask = Utils::createBitMask(1, 2);
    Utils::printBits(mask);
    // todo dont know why mask is not working as expected here and i have to shift
    unsigned char qos = (mask >> 1) & (specificFlags >> 1);

    mask = Utils::createBitMask(0, 0);
    unsigned char retainFlag = mask & specificFlags;

    char* topic = extractUtf8Payload(&data,true);


    unsigned short packetId = -1;
    if(qos > 0){
        memcpy(&packetId, data, sizeof(unsigned short));
        data += sizeof(unsigned short);
    }

    char* msg = extractUtf8Payload(&data,true);

    return new PublishPacket(raw_packet, dupFlag, qos, retainFlag, topic, packetId, msg);
}
