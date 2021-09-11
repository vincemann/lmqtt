//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_DISCONNECTPACKETHANDLER_H
#define LMQTT__SERVER_DISCONNECTPACKETHANDLER_H


#include "PacketHandler.h"
#include "../ServerConnectionManager.h"

class DisconnectPacketHandler : public PacketHandler{
private:
    ServerConnectionManager* _connectionManager;
public:
    DisconnectPacketHandler(PacketIOManager *packetIo, ServerConnectionManager *connectionManager);
    void handle(RawPacket* packet) override;
};


#endif //LMQTT__SERVER_DISCONNECTPACKETHANDLER_H
