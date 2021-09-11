//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBACKPACKETFACTORY_H
#define LMQTT__SERVER_UNSUBACKPACKETFACTORY_H


#include <UnsubAckPacket.h>
#include "PacketFactory.h"

class UnsubAckPacketFactory : public PacketFactory{
public:
    UnsubAckPacket* create(unsigned short packetId);
};


#endif //LMQTT__SERVER_UNSUBACKPACKETFACTORY_H
