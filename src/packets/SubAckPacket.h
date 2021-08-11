//
// Created by vince on 11.08.21.
//

#ifndef LMQTT__SERVER_SUBACKPACKET_H
#define LMQTT__SERVER_SUBACKPACKET_H


#include "RawPacket.h"

class SubAckPacket : public RawPacket{
    unsigned short _packetId;
    unsigned char _retCode;

public:
    SubAckPacket(RawPacket *rawPacket, unsigned short packetId, unsigned char retCode);

    unsigned short getPacketId() const;

    unsigned char getRetCode() const;
};


#endif //LMQTT__SERVER_SUBACKPACKET_H
