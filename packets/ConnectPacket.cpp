//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"
#include "ConnectPacket.h"


ConnectPacket::ConnectPacket(unsigned int length, char *data)
        : RawPacket(CONNECT, 0, length, data) {}

