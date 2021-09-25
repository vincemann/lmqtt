//
// Created by vince on 27.07.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H
#define LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H


#include <SubscribePacketFactory.h>
#include <SubscribeAckPacketHandler.h>
#include "CLIModeHandler.h"
#include "../../topic/ClientTopicRepository.h"

class SubscribeCLIModeHandler : public CLIModeHandler{
private:
    ClientsClientInfoRepository *clientSessionRepository;
    ClientTopicRepository *clientTopicRepository;
    SubscribePacketFactory *subscribePacketFactory;
    SubscribeAckPacketHandler* subscribeAckPacketHandler;

public:
    SubscribeCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                            ConnectPacketFactory *connectPacketFactory, int argc,
                            ClientsClientInfoRepository *clientSessionRepository,
                            SubscribePacketFactory *subscribePacketFactory,
                            SubscribeAckPacketHandler *subscribeAckPacketHandler,
                            ClientTopicRepository *clientTopicRepository);

    void handle() override;
};


#endif //LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H
