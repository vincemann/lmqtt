//
// Created by archdoc on 10/09/2021.
//

#include "UnsubAckPacketFactory.h"

UnsubAckPacket *UnsubAckPacketFactory::create(unsigned short packetId) {
    unsigned char specificFlags = 0;
    Payload* packetIdPayload = new Payload(packetId);

    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 1);
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, UNSUB_ACK);
    return new UnsubAckPacket(rawPacket, packetId);
}
