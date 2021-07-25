//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_MODEHANDLER_H
#define LMQTT__SERVER_MODEHANDLER_H

#include <ConnectPacketFactory.h>
#include "../ClientConnectionManager.h"

class ModeHandler{
public:
    int _argc;
    char **_argv;
    ClientConnectionManager* _clientConnectionManager;
    ConnectPacketFactory* _connectPacketFactory;

    ModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                ConnectPacketFactory *connectPacketFactory, int argc);

    virtual ~ModeHandler();

    // call this after parsing all your cli args
    // -> updates ClientConnectionManager
    void initRoute();
    virtual void handle();

};

#endif //LMQTT__SERVER_MODEHANDLER_H
