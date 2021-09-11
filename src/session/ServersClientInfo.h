//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

#include <vector>
#include <ConnectAckPacketHandler.h>
#include <ostream>

#include "../Subscription.h"


/**
 * Encapsulates server side information about client that is stored permanently (on disk)
 */
class ServersClientInfo {
public:
    char * _clientId;
    // example 3MyTopic qos = 3 topic = MyTopic
    std::vector<Subscription*>* subscriptions;
    //todo add 3. and 4. from ServerSessionState
    explicit ServersClientInfo(char* clientId);

//    friend std::ostream &operator<<(std::ostream &os, const ServerSession &session);
    friend std::ostream &operator<<(std::ostream &os, const ServersClientInfo &session);
};


#endif //LMQTT__SERVER_SESSION_H
