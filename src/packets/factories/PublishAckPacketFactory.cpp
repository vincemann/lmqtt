//
// Created by vince on 12.09.21.
//

#include "PublishAckPacketFactory.h"

PublishAckPacket *PublishAckPacketFactory::create(long int packetId) {
    unsigned char specificFlags = 0;
    Payload* packetIdPayload = new Payload(packetId);

    int payloadLen;
    const Payload* toMerge[] = {packetIdPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 1);
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, PUBLISH_ACK);
    return new PublishAckPacket(rawPacket, packetId);
}
