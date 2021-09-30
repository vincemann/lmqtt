//
// Created by vince on 30.09.21.
//

#ifndef LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H
#define LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H


#include "ClientTopicRepository.h"
#include "ClientQosMessageContainer.h"

class ClientQosTopicRepository {
private:
    char* retransmitDir;
    FileDataManager* fileDataManager;
public:
    void initTopicsDir(char *clientId);
    void saveMsg(char *topic, ClientQosMessageContainer *msg);
    std::vector<ClientQosMessageContainer *> *loadMessages();

    void saveMsg(ClientQosMessageContainer *msg);
};


#endif //LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H
