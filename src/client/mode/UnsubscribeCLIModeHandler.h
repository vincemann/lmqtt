//
// Created by archdoc on 11/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBECLIMODEHANDLER_H
#define LMQTT__SERVER_UNSUBSCRIBECLIMODEHANDLER_H


#include <UnsubscribePacketFactory.h>
#include <UnsubAckPacketHandler.h>
#include "CLIModeHandler.h"

class UnsubscribeCLIModeHandler : public CLIModeHandler{
private:
    ClientsClientInfoRepository *clientsClientInfoRepository;
    UnsubscribePacketFactory *unsubscribePacketFactory;
    UnsubAckPacketHandler* unsubAckPacketHandler;

public:

    UnsubscribeCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                              ConnectPacketFactory *connectPacketFactory, int argc,
                              ClientsClientInfoRepository *clientsClientInfoRepository,
                              UnsubscribePacketFactory *unsubscribePacketFactory,
                              UnsubAckPacketHandler *unsubAckPacketHandler);

    void handle() override;
};


#endif //LMQTT__SERVER_UNSUBSCRIBECLIMODEHANDLER_H
