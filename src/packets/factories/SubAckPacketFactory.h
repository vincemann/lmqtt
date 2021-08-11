//
// Created by vince on 11.08.21.
//

#ifndef LMQTT__SERVER_SUBACKPACKETFACTORY_H
#define LMQTT__SERVER_SUBACKPACKETFACTORY_H


#include "PacketFactory.h"

class SubAckPacketFactory : public PacketFactory{
public:
    SubAckPacket* create(unsigned short packetId, unsigned char retCode);
};


#endif //LMQTT__SERVER_SUBACKPACKETFACTORY_H
