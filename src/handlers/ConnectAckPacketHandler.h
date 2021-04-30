//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTACKPACKETHANDLER_H

#include "PacketHandler.h"

class ConnectAckPacketHandler : public PacketHandler{
public:
    ConnectAckPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo);

    virtual void handle(RawPacket *packet);
};


#endif //LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
