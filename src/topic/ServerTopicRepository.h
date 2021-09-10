//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_SERVERTOPICREPOSITORY_H
#define LMQTT__SERVER_SERVERTOPICREPOSITORY_H


#include <map>
#include "Message.h"
#include "Topic.h"
#include <vector>
#include <FileDataManager.h>
#include <ServersClientInfoRepository.h>

class ServerTopicRepository {
    FileDataManager* _fileDataManager;
    ServersClientInfoRepository* serverSessionRepository;
    char* _topicsDir;

public:
    ServerTopicRepository(FileDataManager *fileDataManager);
    void initTopicFiles(char* topicName);
    void saveMsg(char* topic_c, char* msg);
    // es kann duplikate geben, daher brauche ich das msg obj mit der msg id
    void removeMsg(char* topic, Message* msg);
    Topic* loadTopic(char* topic);
    void saveTopic(Topic* topic);
//    Message* loadMessage(Topic* topic, unsigned long msgId);
    std::vector<Message*>* loadMessages(char* topicName);
    std::vector<Message*>* consumeMessagesStartingFromId(char* topic, unsigned long msgId);
    void subscribe(char* topic);
    void unsubscribe(char* topic, unsigned long lastConsumedMsgId);
    void replaceMessages(char* topic, std::vector<Message*>* msgs);
};


#endif //LMQTT__SERVER_SERVERTOPICREPOSITORY_H
