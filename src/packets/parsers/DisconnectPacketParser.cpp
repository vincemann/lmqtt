//
// Created by vince on 14.07.21.
//

#include <DisconnectPacket.h>
#include "DisconnectPacketParser.h"

RawPacket *DisconnectPacketParser::parse(RawPacket *rawPacket) {
    return new DisconnectPacket(rawPacket);
}
