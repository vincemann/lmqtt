//
// Created by archdoc on 10/09/2021.
//

#include "UnsubscribePacketFactory.h"

UnsubscribePacket* UnsubscribePacketFactory::create(unsigned short packetId, char *topic) {
    unsigned char specificFlags = 2;
    Payload* packetIdPayload = new Payload(packetId);
    Payload* topicPayload = createUtf8Payload(topic);

    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload, topicPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 2);
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, UNSUBSCRIBE);
    return new UnsubscribePacket(rawPacket, packetId, topic);
}