//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H


#include <PublishAckPacketFactory.h>
#include "PacketHandler.h"
#include "../topic/ServerTopicRepository.h"

class ServerPublishPacketHandler : public PacketHandler {
    ServerTopicRepository *topicRepository;
    PublishAckPacketFactory *publishAckPacketFactory;
public:
    void handle(RawPacket *packet) override;

    ServerPublishPacketHandler(PacketIOManager *packetIo,
                               ServerTopicRepository *topicRepository,
                               PublishAckPacketFactory *publishAckPacketFactory);

};


#endif //LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
