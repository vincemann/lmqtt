//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H

#include <ServersClientInfoRepository.h>
#include <ServerConnection.h>
#include <PublishPacketFactory.h>
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../con/ServerConnection.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "../files/FileDataManager.h"
#include "../session/ServersClientInfo.h"
#include "../topic/ServerTopicRepository.h"
#include "../RetransmitMsgHandler.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
protected:
ConnectAckPacketFactory* _connectAckPacketFactory;
ServersClientInfoRepository* _sessionRepository;
ServerConnection* serverConnection;
ServerTopicRepository* topicRepository;
PublishPacketFactory* publishPacketFactory;
RetransmitMsgHandler* retransmitMsgHandler;
void initServerSession(unsigned char cleanSession, char* clientId);
void connAck(int errorCode, unsigned char cleanSessionFlag);
void sendUnconsumedMessages();


public:
    ConnectPacketHandler(ServerConnection *connectionSession, PacketIOManager *packetIo,
                         ConnectAckPacketFactory *connectAckPacketFactory,
                         ServersClientInfoRepository *sessionRepository,
                         ServerTopicRepository *topicRepository,
                         PublishPacketFactory *publishPacketFactory,
                         RetransmitMsgHandler *retransmitMsgHandler);

    void handle(RawPacket *rawPacket) override;
    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
