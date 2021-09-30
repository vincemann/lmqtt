//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H
#define LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H


#include <vector>
#include <ClientPublishAckPacketHandler.h>
#include <PublishPacketFactory.h>
#include "topic/ServerMessageContainer.h"
#include "topic/ClientQosMessageContainer.h"
#include "topic/ClientQosTopicRepository.h"

class ClientRetransmitMsgHandler {
private:
    PacketIOManager *packetIoManager;
    PublishPacketFactory *publishPacketFactory;
//    ClientPublishAckPacketHandler *clientPublishAckPacketHandler;
    ClientQosTopicRepository *clientQosTopicRepository;


public:
    void retransmitMsgs();

    ClientRetransmitMsgHandler(PacketIOManager *packetIoManager, PublishPacketFactory *publishPacketFactory,
                               ClientQosTopicRepository *clientQosTopicRepository);

};


#endif //LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H
