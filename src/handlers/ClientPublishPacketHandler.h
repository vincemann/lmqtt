//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H


#include <RawPacket.h>
#include "PacketHandler.h"
#include "../topic/ServerTopicRepository.h"

class ClientPublishPacketHandler : public PacketHandler {
//    ServerTopicRepository *topicRepository;

public:
    void handle(RawPacket *packet) override;
//    ClientPublishPacketHandler(PacketIOManager *packetIo, ServerTopicRepository *topicRepository);
};


#endif //LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
