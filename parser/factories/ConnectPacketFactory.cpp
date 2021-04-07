//
// Created by vince on 06.04.21.
//

#include "ConnectPacketFactory.h"
#include "../../packets/ConnectPacket.h"
#include "../PacketParsingException.h"

ConnectPacket* ConnectPacketFactory::create(RawPacket* raw_packet) {
    if(raw_packet->getSpecificFlags() != 0){
        // all specific flags must be 0
        throw new PacketParsingException("invalid specific flags");
    }
    return new ConnectPacket(raw_packet->getType(),  raw_packet->getSpecificFlags(),
                             raw_packet->getLength(), raw_packet->getData());
}
