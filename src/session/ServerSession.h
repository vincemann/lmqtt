//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

#include <list>
#include <ConnectAckPacketHandler.h>
#include <ostream>



class ServerSession {
public:
    char * _clientId;
    std::list<char *>* _subscriptions;
    //todo add 3. and 4. from ServerSessionState
    explicit ServerSession(char* clientId);

    friend std::ostream &operator<<(std::ostream &os, const ServerSession &session);

};


#endif //LMQTT__SERVER_SESSION_H
