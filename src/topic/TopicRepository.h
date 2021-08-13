//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_TOPICREPOSITORY_H
#define LMQTT__SERVER_TOPICREPOSITORY_H


#include <map>
#include "Message.h"
#include "Topic.h"
#include <vector>

class TopicRepository {
    std::map<Topic*, std::vector<Message*> *> *_topics;

public:
    TopicRepository();
    void store(Topic* topic,Message* msg);
    void remove(Topic* topic,Message* msg);
    Topic* findTopic(char* topic);
};


#endif //LMQTT__SERVER_TOPICREPOSITORY_H
