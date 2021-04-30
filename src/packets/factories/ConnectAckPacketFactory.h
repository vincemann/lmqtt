//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETFACTORY_H
#define LMQTT__SERVER_CONNECTACKPACKETFACTORY_H

#include "PacketFactory.h"
#include "../ConnectAckPacket.h"

class ConnectAckPacketFactory : public PacketFactory{
public:
    ConnectAckPacket *create(unsigned char returnCode, unsigned char sessionPresent);
};


#endif //LMQTT__SERVER_CONNECTACKPACKETFACTORY_H
