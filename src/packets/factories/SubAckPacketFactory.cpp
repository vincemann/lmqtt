//
// Created by vince on 11.08.21.
//

#include <RawPacket.h>
#include <SubscribeAckPacket.h>
#include "SubAckPacketFactory.h"

SubscribeAckPacket* SubAckPacketFactory::create(unsigned short packetId, unsigned char retCode) {
    unsigned char specificFlags = 0;
    Payload* retCodePayload = new Payload(retCode);
    Payload* packetIdPayload = new Payload(packetId);

    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload,retCodePayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 2);
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, SUBSCRIBE_ACK);
    return new SubscribeAckPacket(rawPacket, packetId, retCode);
}
