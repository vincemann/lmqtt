//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
#define LMQTT__SERVER_CONNECTCLIMODEHANDLER_H


#include "CLIModeHandler.h"
#include "../../ClientRetransmitMsgHandler.h"

class ConnectCLIModeHandler : public CLIModeHandler{
    ClientRetransmitMsgHandler* clientRetransmitMsgHandler;
public:
    void handle() override;

    ConnectCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc,
                          ClientRetransmitMsgHandler *clientRetransmitMsgHandler);
};


#endif //LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
