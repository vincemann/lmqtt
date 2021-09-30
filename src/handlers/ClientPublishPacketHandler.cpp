//
// Created by vince on 10.09.21.
//

#include "ClientPublishPacketHandler.h"


#include <PublishPacket.h>
#include <InvalidPacketException.h>
#include <DisconnectPacket.h>
#include "ServerPublishPacketHandler.h"

void ClientPublishPacketHandler::handle(RawPacket *packet) {
    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);
    printf("received publish packet with qos: %d and packetId: %d\n",publishPacket->getQos(),publishPacket->getPacketId());
    if (publishPacket->getQos() > 2){
        throw InvalidPacketException("qos must be between 0 and 2");
    }
    // dont need to check for duplicates, bc server always only sends once
    if (publishPacket->getQos() == 0){
        if (! topicRepository->topicExists(publishPacket->getTopic())){
            throw InvalidPacketException("Topic, for which publish packet is received, does not exist");
        }
        topicRepository->saveMsg(publishPacket->getTopic(),publishPacket->getMsg());
        printf("successfully saved value: %s for topic: %s\n",publishPacket->getTopic(),publishPacket->getMsg());
        return;
    } else if(publishPacket->getQos() == 1){
        // todo add responses and retransmissions
    }
}

ClientPublishPacketHandler::ClientPublishPacketHandler(PacketIOManager *packetIo,
                                                       ClientTopicRepository *topicRepository) : PacketHandler(
        packetIo), topicRepository(topicRepository) {}
