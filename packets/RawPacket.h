//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_RAWPACKET_H
#define LMQTT__SERVER_RAWPACKET_H

#include "../PacketType.h"

class RawPacket
{
public:

    RawPacket(PacketType type, unsigned char specificFlags,
              unsigned int length, char *data);
    // dynamic cast needs class to be polymorphic, thus needs at least one
    // virtual method
    // https://stackoverflow.com/questions/15114093/getting-source-type-is-not-polymorphic-when-trying-to-use-dynamic-cast
    virtual ~RawPacket() = default;

    PacketType getType() {
        return type;
    }

    unsigned char getSpecificFlags(){
        return specificFlags;
    }

    unsigned int getLength() {
        return length;
    }

    char *getData() {
        return data;
    }


private:
    // fixed header
    PacketType type;
    // 4 bits
    unsigned char specificFlags;
    unsigned int length;
    // variable header + payload
    char* data;
};

#endif //LMQTT__SERVER_RAWPACKET_H
