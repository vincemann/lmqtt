//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H
#define LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H


#include <vector>
#include "topic/ServerMessageContainer.h"
#include "topic/ClientQosMessageContainer.h"

class ClientRetransmitMsgHandler {
    char* qosPath;

public:
    std::vector<ClientQosMessageContainer> getMsgsToRetransmit(unsigned char qos);

};


#endif //LMQTT__SERVER_CLIENTRETRANSMITMSGHANDLER_H
