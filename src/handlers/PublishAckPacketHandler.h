//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHACKPACKETHANDLER_H
#define LMQTT__SERVER_PUBLISHACKPACKETHANDLER_H


#include "PacketHandler.h"
#include "../topic/QosTopicRepository.h"

class PublishAckPacketHandler : public PacketHandler{
    QosTopicRepository* qosTopicRepository;
public:
    void handle(RawPacket *packet) override;

    virtual void onAck(QosMessageContainer* msg);

    PublishAckPacketHandler(PacketIOManager *packetIo, QosTopicRepository *clientQosTopicRepository);
};


#endif //LMQTT__SERVER_PUBLISHACKPACKETHANDLER_H
