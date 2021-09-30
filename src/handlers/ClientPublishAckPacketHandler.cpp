//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include "ClientPublishAckPacketHandler.h"

void ClientPublishAckPacketHandler::handle(RawPacket *packet) {
    PublishAckPacket* publishAckPacket = static_cast<PublishAckPacket*>(packet);
    std::vector<ClientQosMessageContainer*> * msgs = clientQosTopicRepository->loadMessages();
    for (const auto &msg : *msgs){
        if (msg->getId() == publishAckPacket->getPacketId()){
            printf("got ack for packet with id: %ld, %s \n",msg->getId(),msg->getValue());
            printf("removing retransmission file\n");

        }
    }

}
