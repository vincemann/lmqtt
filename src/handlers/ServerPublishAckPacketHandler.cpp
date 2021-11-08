//
// Created by vince on 25.10.21.
//

#include "ServerPublishAckPacketHandler.h"

void ServerPublishAckPacketHandler::handle(RawPacket *packet) {
    PublishAckPacketHandler::handle(packet);
}


void ServerPublishAckPacketHandler::onAck(QosMessageContainer *msg) {
    printf("updating subscription data bc ack arrived for msg\n");

}

ServerPublishAckPacketHandler::ServerPublishAckPacketHandler(PacketIOManager *packetIo,
                                                             QosTopicRepository *clientQosTopicRepository)
        : PublishAckPacketHandler(packetIo, clientQosTopicRepository) {}

