//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include <iostream>
#include "ClientRetransmitMsgHandler.h"


void ClientRetransmitMsgHandler::retransmitMsgs() {
    std::vector<ClientQosMessageContainer *> *msgsToRetransmit = clientQosTopicRepository->loadMessages();
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

ClientRetransmitMsgHandler::ClientRetransmitMsgHandler(PacketIOManager *packetIoManager,
                                                       PublishPacketFactory *publishPacketFactory,
                                                       ClientQosTopicRepository *clientQosTopicRepository,
                                                       ClientPublishAckPacketHandler *publishAckPacketHandler)
        : packetIoManager(packetIoManager), publishPacketFactory(publishPacketFactory),
          clientQosTopicRepository(clientQosTopicRepository), publishAckPacketHandler(publishAckPacketHandler) {}

ClientQosTopicRepository *ClientRetransmitMsgHandler::getClientQosTopicRepository(){
    return clientQosTopicRepository;
}

void ClientRetransmitMsgHandler::saveMsg(ClientQosMessageContainer* msg) {
    this->clientQosTopicRepository->saveMsg(msg);

}
