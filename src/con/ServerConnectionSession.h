//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_SERVERCONNECTIONSESSION_H
#define LMQTT__SERVER_SERVERCONNECTIONSESSION_H

#include <ServerSession.h>
#include "ConnectionSession.h"

class ServerConnectionSession : public ConnectionSession{
public:
    ServerConnectionSession();
    ServerSession* _serverSession;
};


#endif //LMQTT__SERVER_SERVERCONNECTIONSESSION_H
