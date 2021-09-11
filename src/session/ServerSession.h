//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

#include <vector>
#include <ConnectAckPacketHandler.h>
#include <ostream>


/**
 * Encapsulates server side information about client that is stored permanently (on disk)
 */
class ServerSession {
public:
    char * _clientId;
    // example 3MyTopic qos = 3 topic = MyTopic
    std::vector<char *>* _qos_subscriptions;
    //todo add 3. and 4. from ServerSessionState
    explicit ServerSession(char* clientId);

//    friend std::ostream &operator<<(std::ostream &os, const ServerSession &session);
    friend std::ostream &operator<<(std::ostream &os, const ServerSession &session);
};


#endif //LMQTT__SERVER_SESSION_H
