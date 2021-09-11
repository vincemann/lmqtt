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
    void initTopicFiles(char* topicName);
    void store(char* topic_c, char* msg);
    void remove(Topic* topic,Message* msg);
    Topic* loadTopic(char* topic);
    void saveTopic(Topic* topic);
//    Message* loadMessage(Topic* topic, unsigned long msgId);
    std::vector<Message*>* loadMessages(char* topicName);
    std::vector<Message*>* consumeMessagesStartingFromId(char* topic, unsigned long msgId);
    void subscribe(char* topic);
    void unsubscribe(char* topic, unsigned long lastConsumedMsgId);
    void replaceMessages(char* topic, std::vector<Message*>* msgs);
};


#endif //LMQTT__SERVER_TOPICREPOSITORY_H
