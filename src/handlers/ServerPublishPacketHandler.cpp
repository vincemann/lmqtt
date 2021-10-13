//
// Created by vince on 10.09.21.
//

#include <PublishPacket.h>
#include <InvalidPacketException.h>
#include <DisconnectPacket.h>
#include "ServerPublishPacketHandler.h"

extern int NO_PUB_ACK_COUNT;
extern int NO_PUB_ACK_COUNT_START;
int PUB_ACK_COUNT = 0;


void ServerPublishPacketHandler::handle(RawPacket *packet) {
    if (NO_PUB_ACK_COUNT > 0){
        if (PUB_ACK_COUNT >= NO_PUB_ACK_COUNT_START){
            printf("not acking publish packet for test reasons, count: %d\n", NO_PUB_ACK_COUNT);
            NO_PUB_ACK_COUNT-=1;
            exit(1);
            return;
        }
    }
    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);
    printf("received publish packet with qos: %d and packetId: %d\n",publishPacket->getQos(),publishPacket->getPacketId());
    if (publishPacket->getQos() > 2){
        throw InvalidPacketException("qos must be between 0 and 2");
    }

    bool topicExists = topicRepository->topicExists(publishPacket->getTopic());
    if (topicExists == 0){
        printf("topic %s does not exist yet, creating..\n", publishPacket->getTopic());
        printf("init msg %s will be dismissed\n",publishPacket->getMsg());
        topicRepository->saveTopic(new Topic(publishPacket->getTopic()));
        // if topic did not exist yet, there cant be any subscribers, so the msg will be lost intentionally
        // and this will solely be used to create the topic
    } else{
        topicRepository->saveMsg(publishPacket->getTopic(), publishPacket->getMsg());
    }
    if (publishPacket->getQos() == 0 ){
        printf("qos of published value is 0, no response to client\n");
    } else if (publishPacket->getQos() == 1){
        if (publishPacket->getDupFlag() != 0){
            throw InvalidPacketException("when qos is 1, dup must be 0\n");
        }
        printf("qos of published value is 1, sending one puback to client\n");
        PublishAckPacket* ackPacket = publishAckPacketFactory->create(publishPacket->getPacketId());
        _packetIo->sendPacket(ackPacket);
    }
    PUB_ACK_COUNT+=1;
    // todo add responses and retransmissions
}

ServerPublishPacketHandler::ServerPublishPacketHandler(PacketIOManager *packetIo,
                                                       ServerTopicRepository *topicRepository,
                                                       PublishAckPacketFactory *publishAckPacketFactory)
        : PacketHandler(packetIo), topicRepository(topicRepository), publishAckPacketFactory(publishAckPacketFactory) {}
