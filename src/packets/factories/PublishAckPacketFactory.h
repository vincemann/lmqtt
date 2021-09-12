//
// Created by vince on 12.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHACKPACKETFACTORY_H
#define LMQTT__SERVER_PUBLISHACKPACKETFACTORY_H


#include <PublishAckPacket.h>
#include "PacketFactory.h"

class PublishAckPacketFactory : public PacketFactory{

    PublishAckPacket create(unsigned long packetId);

};


#endif //LMQTT__SERVER_PUBLISHACKPACKETFACTORY_H
