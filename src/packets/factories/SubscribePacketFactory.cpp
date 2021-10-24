//
// Created by derdoc on 7/4/21.
//

#include "SubscribePacketFactory.h"
#include "PacketType.h"
#include <string.h>

SubscribePacket *SubscribePacketFactory::create(int packetId,
                               char *topic, unsigned char qos) {
    unsigned char specificFlags = 2;

    Payload* packetIdPayload = new Payload(packetId);
    Payload* topicPayload = PacketFactory::createUtf8Payload(topic);
    Payload* qosPayload = new Payload(qos);


    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload,topicPayload,qosPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 3);

    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, SUBSCRIBE);
    return new SubscribePacket(rawPacket, packetId, topic, qos);
}

