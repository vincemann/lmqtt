//
// Created by vince on 14.08.21.
//

#include <cstring>
#include <iostream>
#include <Utils.h>
#include "TopicRepository.h"
#include <stdlib.h>

#include "../json.hpp"

TopicRepository::TopicRepository(FileDataManager *fileDataManager) : _fileDataManager(fileDataManager) {
//    _topics = new std::map<Topic *, std::vector<Message *> *>();
    const char *targetDir = "/.lmqtt/server/topics/";
    char *home = getenv("HOME");
    char *dir = (char *) malloc(strlen(home) + strlen(targetDir) + 1);
    strcpy(dir, home);
    strcat(dir, targetDir);
    this->_topicsDir = dir;
    Utils::createHomeDirectoryChain(_topicsDir);
}

void TopicRepository::store(Topic *topic, Message *msg) {
    using json = nlohmann::json;
    json j;

    char* topicDir = strdup(_topicsDir);
    strcat(topicDir, topic->getTopic());
    unsigned char topicExists = _fileDataManager->exists(_topicsDir, topic->getTopic());

    if (topicExists == 0){
        // if topic does not exist, store topic file and its init content
        j["topic"] = {
                {"topic_value",                  topic->getTopic()},
                {"subscribed_users_count", topic->getSubscribedUserCount()},
                {"last_msg_id_published",  topic->getLastMsgIdPublished()}
        };
        // create topics topicDir
        std::string jsonString = j.dump();
        Utils::createDirectory(topicDir);
        _fileDataManager->store(topicDir, "topic", Utils::toCharP(&jsonString));
        _fileDataManager->store(topicDir,"messages", Utils::toCharP(""));
    } else{

        char* topicJson = _fileDataManager->find(topicDir,"topic");
        json j = json::parse(topicJson);
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            if (it.key() == "last_msg_id_published"){
                std::string s = it.value().get<std::string>();
                char* last_msg_id_published_s = Utils::toCharP(&s);
                long last_msg_id_published = strtol(last_msg_id_published_s,NULL,10);
            }
        }
        auto j2 = j.get<std::string>();
        char* last_msg_id_published_string = Utils::toCharP();
        j["last_msg_id_published"]

        // create methods for loading topics, creating whole topic objects
        // the same for msges maybe

    }




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


    /*
     * Vllt msg repo einführen, damit ein laden der topic info nicht immer ein laden aller
     * msges des topics zur folge hat und dann einfach dir structure:
     * ~/.lmqtt/server/topics/topicFoo/messages
     * ~/.lmqtt/server/topics/topicFoo/topic
     * ~/.lmqtt/server/topics/topicBar/messages
     * ~/.lmqtt/server/topics/topicBar/topic
     */
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
    _fileDataManager->store(_topicsDir, topic->getTopic(), pJsonString);
}

void TopicRepository::remove(Topic *topic, Message *msg) {

}

Topic *TopicRepository::loadTopic(char *topic) {
    //

    for (auto const &entry : *_topics) {
        Topic *cmp_topic = entry.first;
        if (strcmp(topic, cmp_topic->getTopic()) == 0) {
            return cmp_topic;
        }
    }
    return 0;
}

Message *TopicRepository::loadMessage(Topic *topic, unsigned long msgId) {
    return nullptr;
}

void TopicRepository::remove(Topic *topic) {

}

void TopicRepository::store(Topic *topic) {

}

std::vector<Message *> TopicRepository::loadMessagesStartingFromIndex(Topic *topic, unsigned long msgId) {
    return std::vector<Message *>();
}
