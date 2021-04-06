//
// Created by vince on 06.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETFACTORY_H
#define LMQTT__SERVER_CONNECTPACKETFACTORY_H

#include "../packets/ConnectPacket.h"
#include "../packets/RawPacket.h"

class ConnectPacketFactory {
public:
    ConnectPacket create(RawPacket* raw_packet);
};


#endif //LMQTT__SERVER_CONNECTPACKETFACTORY_H
