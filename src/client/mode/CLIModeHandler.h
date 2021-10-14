//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CLIMODEHANDLER_H
#define LMQTT__SERVER_CLIMODEHANDLER_H

#include <ConnectPacketFactory.h>
#include "../ClientConnectionManager.h"

class CLIModeHandler{
public:
    int _argc;
    char **_argv;
    ClientConnectionManager* clientConnectionManager;
    ConnectPacketFactory* _connectPacketFactory;

    CLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                   ConnectPacketFactory *connectPacketFactory, int argc);

    virtual ~CLIModeHandler();

    // call this after parsing all your cli args
    // -> updates ClientConnectionManager
    void initRoute();
    virtual void handle();

};

#endif //LMQTT__SERVER_CLIMODEHANDLER_H
