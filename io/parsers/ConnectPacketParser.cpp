//
// Created by vince on 06.04.21.
//

#include "ConnectPacketParser.h"
#include "../../packets/ConnectPacket.h"
#include "../exception/PacketParsingException.h"

RawPacket* ConnectPacketParser::parse(RawPacket* raw_packet) {
    if(raw_packet->getSpecificFlags() != 0){
        // all specific flags must be 0
        throw new PacketParsingException("invalid specific flags");
    }
    return new ConnectPacket(raw_packet->getLength(), raw_packet->getData());
}
