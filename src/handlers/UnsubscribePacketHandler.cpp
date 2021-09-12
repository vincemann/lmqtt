//
// Created by archdoc on 10/09/2021.
//

#include <UnsubscribePacket.h>
#include "UnsubscribePacketHandler.h"
#include "../topic/ServerTopicRepository.h"
#include <InvalidPacketException.h>
#include <SubAckPacketFactory.h>




void UnsubscribePacketHandler::handle(RawPacket *packet) {
    UnsubscribePacket* unsubscribePacket = static_cast<UnsubscribePacket*>(packet);
    if (unsubscribePacket->getSpecificFlags() != 2){
        throw InvalidPacketException("Specific Flags must be 2 (reserved)");
    }

    if (strlen(unsubscribePacket->getTopic()) <= 1){
        printf("topic len must be > 1");
    }
    Topic* storedTopic = topicRepository->loadTopic(unsubscribePacket->getTopic());
    if (storedTopic == 0){
        printf("Topic does not exist");
    }

    ServersClientInfo* currentClient = _serverConnection->serversClientInfo;
    //todo  for loop over clients subscriptions, find matching topic name, extract last consumed msg id from obj
//    currentClient->subscriptions
    //    todo: get lastConsumedMsgId from subscription, remove subscription
    unsigned long lastConsumedMsgId;
    topicRepository->unsubscribe(unsubscribePacket->getTopic(), lastConsumedMsgId);
    UnsubAckPacket* unsubAckPacket = _unsubAckPacketFactory->create(unsubscribePacket->getPacketId());
    _packetIo->sendPacket(unsubAckPacket);



}

UnsubscribePacketHandler::UnsubscribePacketHandler(PacketIOManager *packetIo,
                                                   ServersClientInfoRepository *serversClientInfoRepository,
                                                   ServerConnection *serverConnection,
                                                   UnsubAckPacketFactory *unsubAckPacketFactory,
                                                   ServerTopicRepository *topicRepository) : PacketHandler(packetIo),
                                                                                             serversClientInfoRepository(
                                                                                                     serversClientInfoRepository),
                                                                                             _serverConnection(
                                                                                                     serverConnection),
                                                                                             _unsubAckPacketFactory(
                                                                                                     unsubAckPacketFactory),
                                                                                             topicRepository(
                                                                                                     topicRepository) {}

