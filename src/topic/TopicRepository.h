//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_TOPICREPOSITORY_H
#define LMQTT__SERVER_TOPICREPOSITORY_H


#include <map>
#include "Message.h"
#include "Topic.h"
#include <vector>
#include <FileDataManager.h>

class TopicRepository {
    std::map<Topic*, std::vector<Message*> *> *_topics;
    FileDataManager* fileDataManager;
    char* _topicsDir;

public:
    TopicRepository(FileDataManager *fileDataManager);
    void store(Topic* topic,Message* msg);
    void remove(Topic* topic,Message* msg);
    Topic* loadTopic(char* topic);
};


#endif //LMQTT__SERVER_TOPICREPOSITORY_H
