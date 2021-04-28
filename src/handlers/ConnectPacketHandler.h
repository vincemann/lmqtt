//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../Session.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{

public:
    ConnectPacketHandler(Session *session);
    void handle(RawPacket *rawPacket);
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
