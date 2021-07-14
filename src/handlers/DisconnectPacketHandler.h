//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_DISCONNECTPACKETHANDLER_H
#define LMQTT__SERVER_DISCONNECTPACKETHANDLER_H


#include "PacketHandler.h"
#include "../ConnectionManager.h"

class DisconnectPacketHandler : public PacketHandler{
private:
    ConnectionManager* _connectionManager;
public:
    DisconnectPacketHandler(PacketIOManager *packetIo, ConnectionManager *connectionManager);
    void handle(RawPacket* packet) override;
};


#endif //LMQTT__SERVER_DISCONNECTPACKETHANDLER_H
