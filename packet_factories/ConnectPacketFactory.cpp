//
// Created by vince on 06.04.21.
//

#include "ConnectPacketFactory.h"
#include "../packets/ConnectPacket.h"

ConnectPacket* ConnectPacketFactory::create(RawPacket* raw_packet) {
    return new ConnectPacket(raw_packet->getType(),  raw_packet->getSpecificFlags(),
                             raw_packet->getLength(), raw_packet->getData());
}
