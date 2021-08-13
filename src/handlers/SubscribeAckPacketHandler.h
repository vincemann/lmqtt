//
// Created by vince on 12.08.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H
#define LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H


#include <ClientConnection.h>
#include "PacketHandler.h"

class SubscribeAckPacketHandler : public PacketHandler{
private:
    ClientConnection* clientConnection;
public:
    SubscribeAckPacketHandler(PacketIOManager *packetIo, ClientConnection *clientConnection);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H
