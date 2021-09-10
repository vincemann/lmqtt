//
// Created by vince on 10.09.21.
//

#include <PublishPacket.h>
#include <InvalidPacketException.h>
#include <DisconnectPacket.h>
#include "ServerPublishPacketHandler.h"

void ServerPublishPacketHandler::handle(RawPacket *packet) {
    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);
    if (publishPacket->getQos() > 2){
        throw InvalidPacketException("qos must be between 0 and 2");
    }

    topicRepository->store(publishPacket->getTopic(),publishPacket->getMsg());
    if (publishPacket->getQos() == 0 ){
        printf("qos of published msg is 0, no response to client\n");
    }
    // todo add responses and retransmissions
}

ServerPublishPacketHandler::ServerPublishPacketHandler(PacketIOManager *packetIo, TopicRepository *topicRepository)
        : PacketHandler(packetIo), topicRepository(topicRepository) {}
