//
// Created by vince on 14.08.21.
//

#include <cstring>
#include <iostream>
#include "TopicRepository.h"

#include "../json.hpp"

TopicRepository::TopicRepository(FileDataManager *fileDataManager) : fileDataManager(fileDataManager) {
    _topics = new std::map<Topic *, std::vector<Message *> *>();
    const char *targetDir = "/.lmqtt/server/topics";
    char *home = getenv("HOME");
    char *dir = (char *) malloc(strlen(home) + strlen(targetDir) + 1);
    strcpy(dir, home);
    strcat(dir, targetDir);
    this->_topicsDir = dir;
}

void TopicRepository::store(Topic *topic, Message *msg) {
    using json = nlohmann::json;
    json j;

    /*
     *  topic json nur erstellen, wenn es den file namens topic noch nicht gibt
     *  msg json an liste von msg json obj anfügen
     *  evtl aus performance gründen, die letzte zeile(n) : "]"
     *  kurz löschen, dann einfach den msg json eintrag ran cat'n und
     *  letzte zeile(n) wieder anfügen
     *
     *  ist wahrscheinlich schneller als alle msges zu laden, die map zu konstruieren, das über die
     *  map API einbinden und dann wieder mit json dumps den updated string komplett den file damit replacen
     */
    j["topic"] = {{"topic",                  topic->getTopic()},
                  {"subscribed_users_count", topic->getSubscribedUserCount()},
                  {"last_msg_id_published",  topic->getLastMsgIdPublished()}
    };

    j["msgs"] = {
            {"msg",
                    {"id", msg->getId()},
                    {"msg_value", msg->getMsg()},
                    {"unconsumed_user_count", msg->getUnconsumedUserCount()}
            }
    };
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of topic file: " << pJsonString << "\n";
    fileDataManager->store(_topicsDir, topic->getTopic(), pJsonString);
}

void TopicRepository::remove(Topic *topic, Message *msg) {

}

Topic *TopicRepository::loadTopic(char *topic) {

    for (auto const &entry : *_topics) {
        Topic *cmp_topic = entry.first;
        if (strcmp(topic, cmp_topic->getTopic()) == 0) {
            return cmp_topic;
        }
    }
    return 0;
}
