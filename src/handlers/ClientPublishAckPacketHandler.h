//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTPUBLISHACKPACKETHANDLER_H
#define LMQTT__SERVER_CLIENTPUBLISHACKPACKETHANDLER_H


#include "PacketHandler.h"
#include "../topic/ClientQosTopicRepository.h"

class ClientPublishAckPacketHandler : public PacketHandler{
    ClientQosTopicRepository* clientQosTopicRepository;
public:
    void handle(RawPacket *packet) override;

};


#endif //LMQTT__SERVER_CLIENTPUBLISHACKPACKETHANDLER_H
