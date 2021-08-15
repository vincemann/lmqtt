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
    FileDataManager* _fileDataManager;
    char* _topicsDir;

public:
    TopicRepository(FileDataManager *fileDataManager);
    void store(Topic* topic,Message* msg);
    void store(Topic* topic);
    void remove(Topic* topic,Message* msg);
    void remove(Topic* topic);
    Topic* loadTopic(char* topic);
    Message* loadMessage(Topic* topic, unsigned long msgId);
    std::vector<Message*> loadMessagesStartingFromIndex(Topic* topic, unsigned long msgId);
};


#endif //LMQTT__SERVER_TOPICREPOSITORY_H
