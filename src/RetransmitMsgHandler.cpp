//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include <iostream>
#include "RetransmitMsgHandler.h"


void RetransmitMsgHandler::retransmitMsgs() {
    std::vector<QosMessageContainer *> *msgsToRetransmit = qosTopicRepository->loadMessages();
    try {
        for (const auto &msg : *msgsToRetransmit) {
            printf("retransmitting msg: value : %s, id: %d , qos: %d and topic: %s\n", msg->getValue(), msg->getId(),
                   msg->getQos(), msg->getTopic());
            if (msg->getQos() == 1) {
                PublishPacket *republishPacket = publishPacketFactory->create(msg->getQos(), 0, msg->getTopic(),
                                                                              msg->getValue(), 0,msg->getId());
                packetIoManager->sendPacket(republishPacket);
                PublishAckPacket *pubackPacket = static_cast<PublishAckPacket *>(packetIoManager->readPacket());
                publishAckPacketHandler->handle(pubackPacket);
            } else if (msg->getQos() == 2) {
                //todo impl
            }
        }
    } catch (const std::exception &e) {
        // if exception occurs close connection
        printf("problem retransmitting packet\n");
        std::cout << "exception occurred:" << "\n";
        std::cout << e.what() << "\n";
    }

}

RetransmitMsgHandler::RetransmitMsgHandler(PacketIOManager *packetIoManager,
                                           PublishPacketFactory *publishPacketFactory,
                                           QosTopicRepository *clientQosTopicRepository,
                                           PublishAckPacketHandler *publishAckPacketHandler)
        : packetIoManager(packetIoManager), publishPacketFactory(publishPacketFactory),
          qosTopicRepository(clientQosTopicRepository), publishAckPacketHandler(publishAckPacketHandler) {}

QosTopicRepository *RetransmitMsgHandler::getQosTopicRepository(){
    return qosTopicRepository;
}

void RetransmitMsgHandler::saveMsg(QosMessageContainer* msg) {
    this->qosTopicRepository->saveMsg(msg);

}
