//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
#define LMQTT__SERVER_CONNECTCLIMODEHANDLER_H


#include "CLIModeHandler.h"

class ConnectCLIModeHandler : public CLIModeHandler{
public:
    void handle() override;
    ConnectCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc);
};


#endif //LMQTT__SERVER_CONNECTCLIMODEHANDLER_H
