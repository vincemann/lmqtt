//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H


#include "PacketHandler.h"
#include "../topic/TopicRepository.h"

class ServerPublishPacketHandler : public PacketHandler {
    TopicRepository *topicRepository;
public:
    void handle(RawPacket *packet) override;

    ServerPublishPacketHandler(PacketIOManager *packetIo, TopicRepository *topicRepository);

};


#endif //LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
