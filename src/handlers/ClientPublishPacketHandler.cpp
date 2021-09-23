//
// Created by vince on 10.09.21.
//

#include "ClientPublishPacketHandler.h"


#include <PublishPacket.h>
#include <InvalidPacketException.h>
#include <DisconnectPacket.h>
#include "ServerPublishPacketHandler.h"

void ClientPublishPacketHandler::handle(RawPacket *packet) {
//    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);
//    printf("received publish packet with qos: %d and packetId: %d\n",publishPacket->getQos(),publishPacket->getPacketId());
//    if (publishPacket->getQos() > 2){
//        throw InvalidPacketException("qos must be between 0 and 2");
//    }
//    Topic* topic = topicRepository->loadTopic(publishPacket->getTopic());
//    if (topic == 0){
//        topicRepository->saveTopic(new Topic(publishPacket->getTopic()));
//    }
//    topicRepository->saveMsg(publishPacket->getTopic(), publishPacket->getMsg());
//    if (publishPacket->getQos() == 0 ){
//        printf("qos of published msg is 0, no response to client\n");
//    }
//    // todo add responses and retransmissions
}
//
//ClientPublishPacketHandler::ClientPublishPacketHandler(PacketIOManager *packetIo,
//                                                       ServerTopicRepository *topicRepository) : PacketHandler(
//        packetIo), topicRepository(topicRepository) {}
