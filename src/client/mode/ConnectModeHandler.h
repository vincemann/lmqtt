//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CONNECTMODEHANDLER_H
#define LMQTT__SERVER_CONNECTMODEHANDLER_H


#include "ModeHandler.h"

class ConnectModeHandler : public ModeHandler{
public:
    void handle() override;

    ConnectModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                       ConnectPacketFactory *connectPacketFactory, int argc);
};


#endif //LMQTT__SERVER_CONNECTMODEHANDLER_H
