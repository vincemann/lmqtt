//
// Created by vince on 26.09.21.
//

#ifndef LMQTT__SERVER_CLIENTDISCONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CLIENTDISCONNECTPACKETHANDLER_H


#include "PacketHandler.h"
#include "../client/ClientConnectionManager.h"

class ClientDisconnectPacketHandler : public PacketHandler{
private:
    ClientConnectionManager* clientConnectionManager;
public:
    void handle(RawPacket *packet) override;

    ClientDisconnectPacketHandler(PacketIOManager *packetIo, ClientConnectionManager *clientConnectionManager);
};


#endif //LMQTT__SERVER_CLIENTDISCONNECTPACKETHANDLER_H
