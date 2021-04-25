//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_RAWPACKET_H
#define LMQTT__SERVER_RAWPACKET_H

#include "PacketType.h"
#include "RawPacket.h"
#include "factories/PacketFactory.h"

class RawPacket
{
public:
    RawPacket(unsigned char specificFlags,unsigned char *data, unsigned int length, PacketType type);

    RawPacket(RawPacket *rawPacket);
    RawPacket(){}
    ~RawPacket(){
        delete _data;
    }

    PacketType getType() const {
        return _type;
    }

    unsigned char getSpecificFlags() const {
        return _specificFlags;
    }

    unsigned int getLength() const {
        return _length;
    }

    unsigned char *getData() const {
        return _data;
    }


private:

    // 4 bits
    unsigned char _specificFlags;
    // variable header + payload
    unsigned char* _data;
    unsigned int _length;
    PacketType _type;


};

#endif //LMQTT__SERVER_RAWPACKET_H
