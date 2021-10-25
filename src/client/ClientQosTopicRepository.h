//
// Created by vince on 25.10.21.
//

#ifndef LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H
#define LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H


#include "../topic/QosTopicRepository.h"

class ClientQosTopicRepository : public QosTopicRepository{
public:
    void initTopicsDir(char *clientId) override;

    ClientQosTopicRepository(FileDataManager *fileDataManager);
};


#endif //LMQTT__SERVER_CLIENTQOSTOPICREPOSITORY_H
