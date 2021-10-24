//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_SERVERCONNECTION_H
#define LMQTT__SERVER_SERVERCONNECTION_H

#include <ServersClientInfo.h>
#include "ServersClientInfoRepository.h"
#include "Connection.h"

/**
 * Hols all information the lasts as long as a connection with a client (in ram)
 */
class ServerConnection : public Connection{
private:
    ServersClientInfo* serversClientInfo;
    ServersClientInfoRepository* serversClientInfoRepository;
public:
    ServerConnection(ServersClientInfoRepository *serversClientInfoRepository);

    void setServersClientInfo(ServersClientInfo *serversClientInfo);

    ServersClientInfo *loadServersClientInfo() const;
};


#endif //LMQTT__SERVER_SERVERCONNECTION_H
