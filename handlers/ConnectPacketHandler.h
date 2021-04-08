//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{

public:
    void handle(RawPacket *packet);
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
