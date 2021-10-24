//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H


#include <ServerConnection.h>
#include <UnsubAckPacketFactory.h>
#include <ServersClientInfoRepository.h>
#include "../topic/ServerTopicRepository.h"
#include "PacketHandler.h"
#include "../topic/ServerTopicRepository.h"

class UnsubscribePacketHandler : public PacketHandler{
private:
    UnsubAckPacketFactory* _unsubAckPacketFactory;
    ServerTopicRepository* topicRepository;
public:
    UnsubscribePacketHandler(PacketIOManager *packetIo, UnsubAckPacketFactory *unsubAckPacketFactory,
                             ServerTopicRepository *topicRepository);

    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKETHANDLER_H
