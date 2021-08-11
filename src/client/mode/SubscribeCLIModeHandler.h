//
// Created by vince on 27.07.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H
#define LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H


#include <SubscribePacketFactory.h>
#include <SubscribeAckPacketHandler.h>
#include "CLIModeHandler.h"

class SubscribeCLIModeHandler : public CLIModeHandler{
private:
    ClientSessionRepository *clientSessionRepository;
    SubscribePacketFactory *subscribePacketFactory;
    SubscribeAckPacketHandler* subscribeAckPacketHandler;

public:
    SubscribeCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                            ConnectPacketFactory *connectPacketFactory, int argc,
                            ClientSessionRepository *clientSessionRepository,
                            SubscribePacketFactory *subscribePacketFactory,
                            SubscribeAckPacketHandler* subscribeAckPacketHandler);

    void handle() override;
};


#endif //LMQTT__SERVER_SUBSCRIBECLIMODEHANDLER_H
