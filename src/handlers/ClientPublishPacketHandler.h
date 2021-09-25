//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H


#include <RawPacket.h>
#include "PacketHandler.h"
#include "../topic/ServerTopicRepository.h"
#include "../topic/ClientTopicRepository.h"

class ClientPublishPacketHandler : public PacketHandler {
    ClientTopicRepository *topicRepository;

public:
    void handle(RawPacket *packet) override;

    ClientPublishPacketHandler(PacketIOManager *packetIo, ClientTopicRepository *topicRepository);
};


#endif //LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
