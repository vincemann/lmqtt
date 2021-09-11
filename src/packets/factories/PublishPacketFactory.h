//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHPACKETFACTORY_H
#define LMQTT__SERVER_PUBLISHPACKETFACTORY_H


#include <PublishPacket.h>
#include "PacketFactory.h"

class PublishPacketFactory : public PacketFactory {
public:

    PublishPacket *create(unsigned short qos, unsigned char retainFlag, char *topic, char *msg,
                          unsigned char dupFlag);
};


#endif //LMQTT__SERVER_PUBLISHPACKETFACTORY_H
