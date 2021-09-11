//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTACKPACKETHANDLER_H

#include <ClientsClientInfoRepository.h>
#include <ClientConnection.h>
#include "PacketHandler.h"

class ConnectAckPacketHandler : public PacketHandler{
public:
    ClientsClientInfoRepository* _clientSessionRepository;
    ClientConnection* _clientConnectionSession;
    ConnectAckPacketHandler(PacketIOManager *packetIo,
                            ClientsClientInfoRepository *clientSessionRepository,
                            ClientConnection *clientConnectionSession);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
