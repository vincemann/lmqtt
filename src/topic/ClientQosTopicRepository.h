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
    std::vector<ClientQosMessageContainer *> *loadMessages();
    void removeMsg(unsigned long msgId);
    void saveMsg(ClientQosMessageContainer *msg);

    void replaceMessages(char *topic, std::vector<ClientQosMessageContainer *> *msgs);

    void replaceMessages(std::vector<ClientQosMessageContainer *> *msgs);
};


#endif //LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H
