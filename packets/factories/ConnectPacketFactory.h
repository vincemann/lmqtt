    //
// Created by vince on 23.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETFACTORY_H
#define LMQTT__SERVER_CONNECTPACKETFACTORY_H
#include "PacketFactory.h"
#include "../RawPacket.h"

class ConnectPacketFactory : PacketFactory {
    virtual RawPacket *create(RawPacket *raw_packet);
};


#endif //LMQTT__SERVER_CONNECTPACKETFACTORY_H
