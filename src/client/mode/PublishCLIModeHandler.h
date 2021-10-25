//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
#define LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H


#include <PublishPacketFactory.h>
#include <PublishAckPacketHandler.h>
#include "CLIModeHandler.h"
#include "../../RetransmitMsgHandler.h"
#include "../../topic/QosTopicRepository.h"

class PublishCLIModeHandler : public CLIModeHandler{
    ClientsClientInfoRepository *clientSessionRepository;
    PublishPacketFactory *publishPacketFactory;
    RetransmitMsgHandler* clientRetransmitMsgHandler;
    PublishAckPacketHandler* clientPublishAckPacketHandler;

public:
    PublishCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc,
                          ClientsClientInfoRepository *clientSessionRepository,
                          PublishPacketFactory *publishPacketFactory,
                          PublishAckPacketHandler *clientPublishAckPacketHandler, RetransmitMsgHandler* clientRetransmitMsgHandler);

    void handle() override;



};


#endif //LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
