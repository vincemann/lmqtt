//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
#define LMQTT__SERVER_CONNECTCLIMODEHANDLER_H


#include "CLIModeHandler.h"
#include "../../RetransmitMsgHandler.h"

class ConnectCLIModeHandler : public CLIModeHandler{
    RetransmitMsgHandler* clientRetransmitMsgHandler;
public:
    void handle() override;

    ConnectCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc,
                          RetransmitMsgHandler *clientRetransmitMsgHandler);
};


#endif //LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
