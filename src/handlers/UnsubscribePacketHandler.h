//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H


#include <ServerSessionRepository.h>
#include <ServerConnection.h>
#include <UnsubAckPacketFactory.h>
#include "../topic/TopicRepository.h"
#include "PacketHandler.h"

class UnsubscribePacketHandler : public PacketHandler{
private:
    ServerSessionRepository* _serverSessionRepository;
    ServerConnection* _serverConnection;
    UnsubAckPacketFactory* _unsubAckPacketFactory;
    TopicRepository* topicRepository;
public:
    UnsubscribePacketHandler(PacketIOManager *packetIo,
                             ServerSessionRepository *serverSessionRepository,
                             UnsubAckPacketFactory *unsubAckPacketFactory,
                             ServerConnection *serverConnection,
                             TopicRepository *topicRepository);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H
