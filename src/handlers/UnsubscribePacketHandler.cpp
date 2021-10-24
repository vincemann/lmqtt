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

    topicRepository->unsubscribe(unsubscribePacket->getTopic());
    UnsubAckPacket* unsubAckPacket = _unsubAckPacketFactory->create(unsubscribePacket->getPacketId());
    _packetIo->sendPacket(unsubAckPacket);
}

UnsubscribePacketHandler::UnsubscribePacketHandler(PacketIOManager *packetIo,
                                                   UnsubAckPacketFactory *unsubAckPacketFactory,
                                                   ServerTopicRepository *topicRepository) : PacketHandler(packetIo),
                                                                                             _unsubAckPacketFactory(
                                                                                                     unsubAckPacketFactory),
                                                                                             topicRepository(
                                                                                                     topicRepository) {}

