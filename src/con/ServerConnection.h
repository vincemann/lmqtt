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

<<<<<<< HEAD
    ServerConnection(ServerSession *serverSession);

    ServerSession* _serverSession;
=======
    ServerConnection(ServersClientInfo *serverSession);

    ServersClientInfo* serversClientInfo;
>>>>>>> 416b1564649cd1236a49f43d4f035cdf8b45bd30
};


#endif //LMQTT__SERVER_SERVERCONNECTION_H
