//
// Created by vince on 11.08.21.
//

#include <RawPacket.h>
#include <SubAckPacket.h>
#include "SubAckPacketFactory.h"

SubAckPacket* SubAckPacketFactory::create(unsigned short packetId, unsigned char retCode) {
    unsigned char specificFlags = 0;
    unsigned char *payload = new unsigned char[3];
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, 3, SUBSCRIBE_ACK);
    return new SubAckPacket(rawPacket,packetId,retCode);
}
