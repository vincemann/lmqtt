//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"

RawPacket::RawPacket(PacketType type,
                     bool[4] specificFlags,
                     unsigned int length,
                     char *data) :
        type(type),
        specificFlags(specificFlags),
        length(length),
        data(data) {}

