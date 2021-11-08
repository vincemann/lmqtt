//
// Created by vince on 25.10.21.
//

#ifndef LMQTT__SERVER_SERVERPUBLISHACKPACKETHANDLER_H
#define LMQTT__SERVER_SERVERPUBLISHACKPACKETHANDLER_H


#include "PacketHandler.h"
#include "../topic/QosTopicRepository.h"
#include "PublishAckPacketHandler.h"

class ServerPublishAckPacketHandler : public PublishAckPacketHandler{
public:
    ServerPublishAckPacketHandler(PacketIOManager *packetIo, QosTopicRepository *clientQosTopicRepository);
    void onAck(QosMessageContainer* msg) override;
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_SERVERPUBLISHACKPACKETHANDLER_H
