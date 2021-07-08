//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H

#include <ServerSessionRepository.h>
#include <ServerConnection.h>
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../con/ServerConnection.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "../files/FileDataManager.h"
#include "../session/ServerSession.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
protected:
ConnectAckPacketFactory* _connectAckPacketFactory;
ServerSessionRepository* _sessionRepository;
ServerConnection* _connectionSession;
void initServerSession(unsigned char cleanSession, char* clientId);
void connAck(int errorCode, unsigned char cleanSessionFlag);


public:
    ConnectPacketHandler(ServerConnection *connectionSession, PacketIOManager *packetIo,
                         ConnectAckPacketFactory *connectAckPacketFactory, ServerSessionRepository *sessionRepository);

    void handle(RawPacket *rawPacket) override;
    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
