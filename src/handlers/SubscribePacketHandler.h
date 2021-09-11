//
// Created by vince on 11.08.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H
#define LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H


#include <ServersClientInfoRepository.h>
#include <ServerConnection.h>
#include <SubAckPacketFactory.h>
#include "PacketHandler.h"
#include "../topic/ServerTopicRepository.h"

class SubscribePacketHandler : public PacketHandler{
private:
    SubAckPacketFactory* _subAckPacketFactory;
    ServerTopicRepository* topicRepository;
public:
    SubscribePacketHandler(PacketIOManager *packetIo,
                           SubAckPacketFactory *subAckPacketFactory,
                           ServerTopicRepository *topicRepository);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_SUBSCRIBEPACKETHANDLER_H
