//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"
#include "ConnectPacket.h"


ConnectPacket::ConnectPacket(PacketType type, unsigned char specificFlags,
                             unsigned int length, char *data)
        : RawPacket(type, specificFlags, length, data) {}

