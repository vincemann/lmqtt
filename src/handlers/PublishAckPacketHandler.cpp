//
// Created by vince on 23.09.21.
//

#include <PublishAckPacket.h>
#include "PublishAckPacketHandler.h"

void PublishAckPacketHandler::handle(RawPacket *packet) {
    PublishAckPacket* publishAckPacket = static_cast<PublishAckPacket*>(packet);
    std::vector<QosMessageContainer*> * msgs = qosTopicRepository->loadMessages();
    std::vector<QosMessageContainer*> * remainingUnAckedMsgs = new std::vector<QosMessageContainer*>();
    printf("checking if saved retransmit msg has id: %d, thus is to delete\n",publishAckPacket->getPacketId());
    for (const auto &msg : *msgs){
        printf("checking saved retransmit msg with id: %d\n",msg->getId());
        if (msg->getId() == publishAckPacket->getPacketId()){
            printf("got ack for packet with id: %d, %s \n",msg->getId(),msg->getValue());
            printf("removing retransmission msg\n");
            onAck(msg);
            continue;
        } else{
            remainingUnAckedMsgs->push_back(msg);
        }
    }
    if (msgs->size() != remainingUnAckedMsgs->size()){
        // remove acked msg from list
        qosTopicRepository->replaceMessages(remainingUnAckedMsgs);
    }
}



PublishAckPacketHandler::PublishAckPacketHandler(PacketIOManager *packetIo,
                                                 QosTopicRepository *clientQosTopicRepository)
        : PacketHandler(packetIo), qosTopicRepository(clientQosTopicRepository) {}

void PublishAckPacketHandler::onAck(QosMessageContainer *msg) {

}

