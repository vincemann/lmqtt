//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_RAWPACKET_H
#define LMQTT__SERVER_RAWPACKET_H

#include "../PacketType.h"

class RawPacket
{
public:

    RawPacket(PacketType type, bool[4] specificFlags,
              unsigned int length, char *data);

    PacketType getType() const {
        return type;
    }

    bool[4] getSpecificFlags() const {
        return specificFlags;
    }

    unsigned int getLength() const {
        return length;
    }

    char *getData() const {
        return data;
    }


private:
    // fixed header
    PacketType type;
    // 4 bits
    bool[4] specificFlags;
    unsigned int length;
    // variable header + payload
    char* data;
};

#endif //LMQTT__SERVER_RAWPACKET_H
