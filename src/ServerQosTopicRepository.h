//
// Created by vince on 25.10.21.
//

#ifndef LMQTT__SERVER_SERVERQOSTOPICREPOSITORY_H
#define LMQTT__SERVER_SERVERQOSTOPICREPOSITORY_H


#include "topic/QosTopicRepository.h"

class ServerQosTopicRepository : public QosTopicRepository{
public:
    void initTopicsDir(char *clientId) override;

    ServerQosTopicRepository(FileDataManager *fileDataManager);
};


#endif //LMQTT__SERVER_SERVERQOSTOPICREPOSITORY_H
