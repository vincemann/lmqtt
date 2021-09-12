//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_SERVERCONNECTION_H
#define LMQTT__SERVER_SERVERCONNECTION_H

#include <ServersClientInfo.h>
#include "Connection.h"

/**
 * Hols all information the lasts as long as a connection with a client (in ram)
 */
class ServerConnection : public Connection{
public:
    ServerConnection();


    ServerConnection(ServersClientInfo *serverSession);
    ServersClientInfo* serversClientInfo;
};


#endif //LMQTT__SERVER_SERVERCONNECTION_H
