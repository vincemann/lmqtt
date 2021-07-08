//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CLIENTCONNECTION_H
#define LMQTT__SERVER_CLIENTCONNECTION_H

#include <ConnectPacket.h>
#include "Connection.h"

class ClientConnection : public Connection{
public:
    ConnectPacket* _connectPacket;

    ClientConnection(ConnectPacket *connectPacket);

    ClientConnection();
};


#endif //LMQTT__SERVER_CLIENTCONNECTION_H
