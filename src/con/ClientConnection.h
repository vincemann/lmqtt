//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CLIENTCONNECTION_H
#define LMQTT__SERVER_CLIENTCONNECTION_H

#include <ConnectPacket.h>
#include "Connection.h"

/**
 * Hols all information the lasts as long as a connection with the server (in ram)
 */
class ClientConnection : public Connection{
public:
    ConnectPacket* _connectPacket;

    ConnectPacket *getConnectPacket() const;

    ClientConnection(ConnectPacket *connectPacket);
    ClientConnection();
};


#endif //LMQTT__SERVER_CLIENTCONNECTION_H
