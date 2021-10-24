//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKETFACTORY_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKETFACTORY_H


#include <UnsubscribePacket.h>
#include "PacketFactory.h"

class UnsubscribePacketFactory : public PacketFactory{
public:
    UnsubscribePacket* create(int packetId, char *topic);
};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKETFACTORY_H
