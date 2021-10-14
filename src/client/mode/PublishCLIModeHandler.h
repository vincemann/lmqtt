//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
#define LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H


#include <PublishPacketFactory.h>
#include <ClientPublishAckPacketHandler.h>
#include "CLIModeHandler.h"
#include "../../ClientRetransmitMsgHandler.h"
#include "../../topic/ClientQosTopicRepository.h"

class PublishCLIModeHandler : public CLIModeHandler{
    ClientsClientInfoRepository *clientSessionRepository;
    PublishPacketFactory *publishPacketFactory;
    ClientRetransmitMsgHandler* clientRetransmitMsgHandler;
    ClientPublishAckPacketHandler* clientPublishAckPacketHandler;

public:
    PublishCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc,
                          ClientsClientInfoRepository *clientSessionRepository,
                          PublishPacketFactory *publishPacketFactory,
                          ClientPublishAckPacketHandler *clientPublishAckPacketHandler, ClientRetransmitMsgHandler* clientRetransmitMsgHandler);

    void handle() override;



};


#endif //LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
