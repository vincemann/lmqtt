//
// Created by archdoc on 10/09/2021.
//

#include <UnsubscribePacket.h>
#include "UnsubscribePacketHandler.h"
#include <InvalidPacketException.h>
#include <SubAckPacketFactory.h>


UnsubscribePacketHandler::UnsubscribePacketHandler(PacketIOManager *packetIo,
                                               ServerSessionRepository *serverSessionRepository,
                                               UnsubAckPacketFactory *unsubAckPacketFactory,
                                               ServerConnection *serverConnection,
                                               TopicRepository *topicRepository): PacketHandler(packetIo),
                                               _serverSessionRepository(serverSessionRepository),
                                               _serverConnection(serverConnection),
                                               _unsubAckPacketFactory(unsubAckPacketFactory),
                                               topicRepository(topicRepository) {}

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

    ServerSession* serverSession = _serverConnection->_serverSession;
    //    todo: get lastConsumedMsgId from subscription, remove subscription
    unsigned long lastConsumedMsgId;
    topicRepository->unsubscribe(unsubscribePacket->getTopic(), lastConsumedMsgId);
    UnsubAckPacket* unsubAckPacket = _unsubAckPacketFactory->create(unsubscribePacket->getPacketId());
    _packetIo->sendPacket(unsubAckPacket);



}
