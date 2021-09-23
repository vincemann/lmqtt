//
// Created by vince on 10.09.21.
//

#include <PublishPacket.h>
#include <InvalidPacketException.h>
#include <DisconnectPacket.h>
#include "ServerPublishPacketHandler.h"

void ServerPublishPacketHandler::handle(RawPacket *packet) {
    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);
    printf("received publish packet with qos: %d and packetId: %d\n",publishPacket->getQos(),publishPacket->getPacketId());
    if (publishPacket->getQos() > 2){
        throw InvalidPacketException("qos must be between 0 and 2");
    }
    Topic* topic = topicRepository->loadTopic(publishPacket->getTopic());
    if (topic == 0){
        topicRepository->saveTopic(new Topic(publishPacket->getTopic()));
    }
    topicRepository->saveMsg(publishPacket->getTopic(), publishPacket->getMsg());
    if (publishPacket->getQos() == 0 ){
        printf("qos of published msg is 0, no response to client\n");
    } else if (publishPacket->getQos() == 1){
        if (publishPacket->getDupFlag() != 0){
            throw InvalidPacketException("when qos is 1, dup must be 0\n");
        }
        printf("qos of published msg is 1, sending one puback to client\n");
        publishAckPacketFactory->create(publishPacket->getPacketId());
    }
    // todo add responses and retransmissions
}

ServerPublishPacketHandler::ServerPublishPacketHandler(PacketIOManager *packetIo,
                                                       ServerTopicRepository *topicRepository,
                                                       PublishAckPacketFactory *publishAckPacketFactory)
        : PacketHandler(packetIo), topicRepository(topicRepository), publishAckPacketFactory(publishAckPacketFactory) {}
