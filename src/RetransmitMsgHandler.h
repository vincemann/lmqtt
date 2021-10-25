//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_RETRANSMITMSGHANDLER_H
#define LMQTT__SERVER_RETRANSMITMSGHANDLER_H


#include <vector>
#include <PublishAckPacketHandler.h>
#include <PublishPacketFactory.h>
#include "topic/ServerMessageContainer.h"
#include "topic/QosMessageContainer.h"
#include "topic/QosTopicRepository.h"

class RetransmitMsgHandler {
private:
    PacketIOManager *packetIoManager;
    PublishPacketFactory *publishPacketFactory;
    QosTopicRepository *qosTopicRepository;
    PublishAckPacketHandler* publishAckPacketHandler;


public:
    void saveMsg(QosMessageContainer* msg);
    void retransmitMsgs();

    RetransmitMsgHandler(PacketIOManager *packetIoManager,
                         PublishPacketFactory *publishPacketFactory,
                         QosTopicRepository *clientQosTopicRepository,
                         PublishAckPacketHandler *publishAckPacketHandler);

    QosTopicRepository *getClientQosTopicRepository();

};


#endif //LMQTT__SERVER_RETRANSMITMSGHANDLER_H
