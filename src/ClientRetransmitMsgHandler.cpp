//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include <iostream>
#include "ClientRetransmitMsgHandler.h"


void ClientRetransmitMsgHandler::retransmitMsgs() {
    std::vector<ClientQosMessageContainer *> *msgsToRetransmit = clientQosTopicRepository->loadMessages();
    std::vector<ClientQosMessageContainer *> *untransmitted = clientQosTopicRepository->loadMessages();
    try {
        for (const auto &msg : *msgsToRetransmit) {
            printf("retransmitting value : %s, id: %d , qos: %d and topic: %s\n", msg->getValue(), msg->getId(),
                   msg->getQos(), msg->getTopic());
            if (msg->getQos() == 1) {
                PublishPacket *republishPacket = publishPacketFactory->create(msg->getQos(), 0, msg->getTopic(),
                                                                              msg->getValue(), 0);
                packetIoManager->sendPacket(republishPacket);
                PublishAckPacket *pubackPacket = static_cast<PublishAckPacket *>(packetIoManager->readPacket());
                if (pubackPacket->getPacketId() == republishPacket->getPacketId()) {
                    printf("got ack for packet with id: %ld, %s \n", msg->getId(), msg->getValue());
                    continue;
                }
            } else if (msg->getQos() == 2) {
                //todo impl
            }
            untransmitted->push_back(msg);
        }
    } catch (const std::exception &e) {
        // if exception occurs close connection
        printf("problem retransmitting packet\n");
        std::cout << "exception occurred:" << "\n";
        std::cout << e.what() << "\n";
    }
    printf("removing retransmitted files from client\n");
    clientQosTopicRepository->replaceMessages(untransmitted);

}

ClientRetransmitMsgHandler::ClientRetransmitMsgHandler(PacketIOManager *packetIoManager,
                                                       PublishPacketFactory *publishPacketFactory,
                                                       ClientQosTopicRepository *clientQosTopicRepository)
        : packetIoManager(packetIoManager), publishPacketFactory(publishPacketFactory),
          clientQosTopicRepository(clientQosTopicRepository) {}
