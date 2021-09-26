    //
// Created by vince on 23.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETFACTORY_H
#define LMQTT__SERVER_CONNECTPACKETFACTORY_H
#include "PacketFactory.h"
#include "../RawPacket.h"
#include "../../packets/ConnectPacket.h"

class ConnectPacketFactory : public PacketFactory {
public:
    ConnectPacket *create(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                          unsigned char willRetain,
                          char *clientId, char *willTopic, char *willMsg, char *username,
                          char *password,unsigned char consume);
    ConnectPacket *create(unsigned char cleanSession,char *clientId,
                          char *username,
                          char *password,unsigned char consume);
};


#endif //LMQTT__SERVER_CONNECTPACKETFACTORY_H
