//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include "ClientPublishAckPacketHandler.h"

void ClientPublishAckPacketHandler::handle(RawPacket *packet) {
    PublishAckPacket* publishAckPacket = static_cast<PublishAckPacket*>(packet);
    std::vector<ClientQosMessageContainer*> * msgs = clientQosTopicRepository->loadMessages();
    std::vector<ClientQosMessageContainer*> * remainingUnAckedMsgs = new std::vector<ClientQosMessageContainer*>();
    printf("checking if saved retransmit msg has id: %d, thus is to delete\n",publishAckPacket->getPacketId());
    for (const auto &msg : *msgs){
        printf("checking saved retransmit msg with id: %d\n",msg->getId());
        if (msg->getId() == publishAckPacket->getPacketId()){
            printf("got ack for packet with id: %d, %s \n",msg->getId(),msg->getValue());
            printf("removing retransmission msg file\n");
            continue;
        } else{
            remainingUnAckedMsgs->push_back(msg);
        }
    }
    if (msgs->size() != remainingUnAckedMsgs->size()){
        // remove acked msg from list
        clientQosTopicRepository->replaceMessages(remainingUnAckedMsgs);
    }


}

ClientPublishAckPacketHandler::ClientPublishAckPacketHandler(PacketIOManager *packetIo,
                                                             ClientQosTopicRepository *clientQosTopicRepository)
        : PacketHandler(packetIo), clientQosTopicRepository(clientQosTopicRepository) {}

