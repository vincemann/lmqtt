//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_SERVERCONNECTION_H
#define LMQTT__SERVER_SERVERCONNECTION_H

#include <ServerSession.h>
#include "Connection.h"

class ServerConnection : public Connection{
public:
    ServerConnection();
    ServerSession* _serverSession;
};


#endif //LMQTT__SERVER_SERVERCONNECTION_H
