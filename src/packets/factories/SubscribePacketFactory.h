//
// Created by derdoc on 7/4/21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEPACKETFACTORY_H
#define LMQTT__SERVER_SUBSCRIBEPACKETFACTORY_H

#include "PacketFactory.h"
#include "../SubscribePacket.h"

class SubscribePacketFactory : public PacketFactory{
public:
    SubscribePacket *create(int packetId,
                            char *topic, unsigned char qos);

};


#endif //LMQTT__SERVER_SUBSCRIBEPACKETFACTORY_H
