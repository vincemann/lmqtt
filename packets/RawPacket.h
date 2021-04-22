//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_RAWPACKET_H
#define LMQTT__SERVER_RAWPACKET_H

#include "PacketType.h"
#include "RawPacket.h"

class RawPacket
{
public:
    RawPacket(unsigned char specificFlags, char *data, unsigned int length, PacketType type)
    : _specific_flags(specificFlags), _data(data), _length(length), _type(type) {}

    RawPacket(RawPacket *rawPacket)
    : _specific_flags(rawPacket->specificFlags), _data( rawPacket->data), _length( rawPacket->_length), _type(rawPacket->_type) {}

    RawPacket(){}
    // dynamic cast needs class to be polymorphic, thus needs at least one
    // virtual method
    // https://stackoverflow.com/questions/15114093/getting-source-type-is-not-polymorphic-when-trying-to-use-dynamic-cast
    virtual ~RawPacket(){
        delete _data;
    }

    PacketType getType() const {
        return _type;
    }

    unsigned char getSpecificFlags() const {
        return _specific_flags;
    }

    unsigned int getLength() const {
        return _length;
    }

    unsigned char *getData() const {
        return _data;
    }


private:
    // 4 bits
    unsigned char _specific_flags;
    // variable header + payload
    char* _data;
    unsigned int _length;
    PacketType _type;
};

#endif //LMQTT__SERVER_RAWPACKET_H
