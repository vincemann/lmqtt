    //
// Created by vince on 23.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETFACTORY_H
#define LMQTT__SERVER_CONNECTPACKETFACTORY_H
#include "PacketFactory.h"
#include "../RawPacket.h"

class ConnectPacketFactory : PacketFactory {
    ConnectPacket *create(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                          unsigned char willRetain,
                          unsigned char *clientId, unsigned char *willTopic, unsigned char *willMsg, unsigned char *username,
                          unsigned char *password);
    ConnectPacket *create(unsigned char cleanSession,unsigned char *clientId,
                          unsigned char *username,
                          unsigned char *password);
};


#endif //LMQTT__SERVER_CONNECTPACKETFACTORY_H
