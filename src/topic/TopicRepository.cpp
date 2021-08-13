//
// Created by vince on 14.08.21.
//

#include <cstring>
#include "TopicRepository.h"


TopicRepository::TopicRepository() {
    _topics = new std::map();
}

void TopicRepository::store(Topic *topic, Message *msg) {

}

void TopicRepository::remove(Topic *topic, Message *msg) {

}

Topic* TopicRepository::findTopic(char *topic) {
    for (auto const & entry : *_topics) {
        Topic* cmp_topic = entry.first;
        if (strcmp(topic,cmp_topic->getTopic()) == 0 ){
            return cmp_topic;
        }
    }
    return 0;
}
