//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_RAWPACKET_H
#define LMQTT__SERVER_RAWPACKET_H

#include "PacketType.h"

class RawPacket
{
public:

    RawPacket(PacketType type, unsigned char specificFlags,
              unsigned int length, char *data);
    // dynamic cast needs class to be polymorphic, thus needs at least one
    // virtual method
    // https://stackoverflow.com/questions/15114093/getting-source-type-is-not-polymorphic-when-trying-to-use-dynamic-cast
    virtual ~RawPacket() = default;

    PacketType getType() const {
        return _type;
    }

    unsigned char getSpecificFlags() const {
        return _specific_flags;
    }

    unsigned int getLength() const {
        return _length;
    }

    char *getData() const {
        return _data;
    }


private:
    // fixed header
    PacketType _type;
    // 4 bits
    unsigned char _specific_flags;
    unsigned int _length;
    // variable header + payload
    char* _data;
};

#endif //LMQTT__SERVER_RAWPACKET_H
