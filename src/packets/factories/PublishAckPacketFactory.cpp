//
// Created by vince on 12.09.21.
//

#include "PublishAckPacketFactory.h"

PublishAckPacket PublishAckPacketFactory::create(unsigned long packetId) {
    unsigned char specificFlags = 4;
    Payload* packetIdPayload = new Payload(packetId);

    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 1);
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, PUB_ACK);
    return PublishAckPacket(rawPacket, packetId);
}
