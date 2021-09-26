//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_SERVERDISCONNECTPACKETHANDLER_H
#define LMQTT__SERVER_SERVERDISCONNECTPACKETHANDLER_H


#include "PacketHandler.h"
#include "../ServerConnectionManager.h"

class ServerDisconnectPacketHandler : public PacketHandler{
private:
    ServerConnectionManager* _connectionManager;
public:
    ServerDisconnectPacketHandler(PacketIOManager *packetIo, ServerConnectionManager *connectionManager);
    void handle(RawPacket* packet) override;
};


#endif //LMQTT__SERVER_SERVERDISCONNECTPACKETHANDLER_H
