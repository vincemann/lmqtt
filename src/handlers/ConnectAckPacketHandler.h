//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTACKPACKETHANDLER_H

#include <ClientSessionRepository.h>
#include <ClientConnection.h>
#include "PacketHandler.h"

class ConnectAckPacketHandler : public PacketHandler{
public:
    ClientSessionRepository* _clientSessionRepository;
    ClientConnection* _clientConnectionSession;
    ConnectAckPacketHandler(PacketIOManager *packetIo,
                            ClientSessionRepository *clientSessionRepository,
                            ClientConnection *clientConnectionSession);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
