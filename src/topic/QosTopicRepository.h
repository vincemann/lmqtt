//
// Created by vince on 30.09.21.
//

#ifndef LMQTT__SERVER_QOSTOPICREPOSITORY_H
#define LMQTT__SERVER_QOSTOPICREPOSITORY_H


#include "ClientTopicRepository.h"
#include "QosMessageContainer.h"
#include <vector>

class QosTopicRepository {
protected:
    char* retransmitDir;
    FileDataManager* fileDataManager;
public:
    QosTopicRepository(FileDataManager *fileDataManager);


    virtual void initTopicsDir(char *clientId);
    std::vector<QosMessageContainer *> *loadMessages();
    void saveMsg(QosMessageContainer *msg);
    void replaceMessages(std::vector<QosMessageContainer *> *msgs);
};


#endif //LMQTT__SERVER_QOSTOPICREPOSITORY_H
