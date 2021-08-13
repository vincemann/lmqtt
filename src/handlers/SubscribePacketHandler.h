//
// Created by vince on 11.08.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H
#define LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H


#include <ServerSessionRepository.h>
#include <ServerConnection.h>
#include <SubAckPacketFactory.h>
#include "PacketHandler.h"
#include "../topic/TopicRepository.h"

class SubscribePacketHandler : public PacketHandler{
private:
    ServerSessionRepository* _serverSessionRepository;
    ServerConnection* _serverConnection;
    SubAckPacketFactory* _subAckPacketFactory;
    TopicRepository* topicRepository;
public:
    SubscribePacketHandler(PacketIOManager *packetIo,
                           ServerSessionRepository *serverSessionRepository,
                           ServerConnection *serverConnection,
                           SubAckPacketFactory *subAckPacketFactory,
                           TopicRepository *topicRepository);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H
