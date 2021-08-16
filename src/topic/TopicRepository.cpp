//
// Created by vince on 14.08.21.
//

#include <cstring>
#include <iostream>
#include <Utils.h>
#include "TopicRepository.h"
#include <stdlib.h>
#include "IllegalSessionStateException.h"

#include "../json.hpp"

TopicRepository::TopicRepository(FileDataManager *fileDataManager) : _fileDataManager(fileDataManager) {
    //    _topics = new std::map<Topic *, std::vector<Message *> *>();
    const char *targetDir = "/.lmqtt/server/topics/";
    char *home = getenv("HOME");
    _topicsDir = Utils::smartstrcat(home, targetDir);
    Utils::createHomeDirectoryChain(_topicsDir);
}

void TopicRepository::store(char *topic_c, char *msg) {

    initTopicFiles(topic_c);

    char *topicDir = Utils::smartstrcat(_topicsDir, topic_c);
    char *msgsJson = _fileDataManager->find(topicDir, "messages");

    Topic *topic = loadTopic(topic_c);
    long msgId = topic->getLastMsgIdPublished() + 1;
    topic->setLastMsgIdPublished(msgId);
    Message *message = new Message(msgId, topic->getSubscribedUserCount(), msg);

    using json = nlohmann::json;
    json j;
    if (strlen(msgsJson) == 0) {
        j = {
                {"msg",
                        "id", message->getId(),
                        "msg_value", message->getMsg(),
                        "unconsumed_user_count", message->getUnconsumedUserCount()
                }
        };
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {"msg",
                        "id", message->getId(),
                        "msg_value", message->getMsg(),
                        "unconsumed_user_count", message->getUnconsumedUserCount()
        };
        j.push_back(jsonMsg);
    }


    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);

    saveTopic(topic);
    _fileDataManager->store(topicDir, "messages", jsonMsgs_c);


//
//
//    using json = nlohmann::json;
//    json j;
//
//
//
//    initTopicFiles(topic_c);
//
//    Topic* topic =  loadTopic(topic_c);
//    long msgId = topic->getLastMsgIdPublished() + 1;
//    topic->setLastMsgIdPublished(msgId);
//
//    std::vector<Message *>* msgs = loadMessages(topic_c);
//    Message* message = new Message(msgId,topic->getSubscribedUserCount(),msg);
//    msgs->push_back(message);
//
//    std::vector<json> jsonMsgs = std::vector<json>();
//
//    for (const auto &item : *msgs) {
//        json jsonMsg = {"msg",
//                        {"id", item->getId()},
//                        {"msg_value", item->getMsg()},
//                        {"unconsumed_user_count", item->getUnconsumedUserCount()}
//        };
//        jsonMsgs.push_back(jsonMsg);
//    }
//
//
//
//    j = jsonMsgs;
//    std::string jsonMsgsString = j.dump();
//    // use util function
//    char* jsonMsgs_c = Utils::toCharP(&jsonMsgsString);
//    char *topicDir = strdup(_topicsDir);
//    strcat(topicDir, topic_c);
//
//    saveTopic(new Topic(topicDir));
//    _fileDataManager->store(topicDir, "messages", jsonMsgs_c);
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

 * ~/.lmqtt/server/topics/topicFoo/messages
 * ~/.lmqtt/server/topics/topicFoo/topic
 * ~/.lmqtt/server/topics/topicBar/messages
 * ~/.lmqtt/server/topics/topicBar/topic
 */

void TopicRepository::saveMessages(char *topic, std::vector<Message *> *msgs) {
    using json = nlohmann::json;
    std::vector<json> jsonMsgs = std::vector<json>();

    char *topicDir = Utils::smartstrcat(_topicsDir, topic);


    for (const auto &item : *msgs) {
        json jsonMsg = {"msg",
                        {
                                "id", item->getId(),
                                "msg_value", item->getMsg(),
                                "unconsumed_user_count", item->getUnconsumedUserCount()
                        }
        };
        jsonMsgs.push_back(jsonMsg);
    }
    json j = jsonMsgs;
    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);
    _fileDataManager->store(topicDir, "messages", jsonMsgs_c);
}

void TopicRepository::remove(Topic *topic, Message *msg) {

}

// expects topic name
Topic *TopicRepository::loadTopic(char *topic) {
    using json = nlohmann::json;

    char *pathToTopicDir = Utils::smartstrcat(_topicsDir, topic);
    //    check file existence
    unsigned char fileExists = _fileDataManager->exists(pathToTopicDir, "topic");
    if (fileExists == 0) {
        throw IllegalSessionStateException("Connection Refused, unacceptable protocol version");
    }

    //    extract values
    unsigned long subscribedUserCount = -1;
    unsigned long lastMsgIdPublished = -1;
    char *topicValue = 0;
    char *topicJson = _fileDataManager->find(pathToTopicDir, "topic");
    json j = json::parse(topicJson);
    // j is array not obj
    // iterating over that array wont work bc of key method ?
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "subscribed_users_count") {
            subscribedUserCount = it.value().get<unsigned long>();
//            std::string s = it.value().get<std::string>();
//            char *subscribed_users_count_s = Utils::toCharP(&s);
//            subscribedUserCount = strtol(subscribed_users_count_s, NULL, 10);
        }
        if (it.key() == "last_msg_id_published") {
            lastMsgIdPublished = it.value().get<unsigned long>();
//            char *last_msg_id_published_s = Utils::toCharP(&s);
//            lastMsgIdPublished = strtol(last_msg_id_published_s, NULL, 10);
        }
        if (it.key() == "topic_value") {
            std::string s = it.value().get<std::string>();
            topicValue = Utils::toCharP(&s);
        }
    }
    return new Topic(lastMsgIdPublished, subscribedUserCount, topicValue);
}

void TopicRepository::saveTopic(Topic *topic) {
    using json = nlohmann::json;
    json j;

    char *topicDir = Utils::smartstrcat(_topicsDir, topic->getTopic());
    j = {
            "topic_value", topic->getTopic(),
            "subscribed_users_count", topic->getSubscribedUserCount(),
            "last_msg_id_published", topic->getLastMsgIdPublished()
    };
    std::string jsonString = j.dump();
    _fileDataManager->store(topicDir, "topic", Utils::toCharP(&jsonString));
}


//Message *TopicRepository::loadMessage(Topic *topic, unsigned long msgId) {
//    return nullptr;
//}


std::vector<Message *> *TopicRepository::consumeMessagesStartingFromId(char *topic, unsigned long lastConsumedMsgId) {
    std::vector<Message *> *msgs = loadMessages(topic);
    std::vector<Message *> *consumedMsgs = new std::vector<Message *>();
    std::vector<Message *> *updatedMsgs = new std::vector<Message *>();


//    std::vector<Message*>::iterator i = msgs->begin();
//    int count = 0;
//    while (i != msgs->end()) {
//        Message *msg = (*i);
//        if (msg->getId() > lastConsumedMsgId) {
//            msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() - 1);
//            consumedMsgs->push_back(msg);
//            ++i;
//        }
//        if (msg->getId() <= 0) {
//            msgs->erase(i++);
//            // get rid of anything < 10
//            msgs->erase(std::remove_if(msgs->begin(), msgs->end(),
//                                   [](int i) { return i == count; }), msgs.end());
//        }

    for (auto &msg : *msgs) {
        if (msg->getId() > lastConsumedMsgId) {
            msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() - 1);
            consumedMsgs->push_back(msg);
            updatedMsgs->push_back(msg);
        }
        if (msg->getId() <= 0) {

        } else {
            updatedMsgs->push_back(msg);
        }
    }
    // update msges meta data
    saveMessages(topic, updatedMsgs);
    delete updatedMsgs;
    delete msgs;
    return consumedMsgs;
}

void TopicRepository::subscribe(char *topicName) {
    Topic *topic = loadTopic(topicName);
    topic->setSubscribedUsersCount(topic->getSubscribedUserCount() + 1);
    std::vector<Message *> *msgs = loadMessages(topicName);
    for (const auto &msg : *msgs) {
        msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() + 1);
    }
    saveMessages(topicName, msgs);
    saveTopic(topic);
}

void TopicRepository::unsubscribe(char *topicName, unsigned long lastConsumedMsgId) {
    char *topicDir = strdup(_topicsDir);
    strcat(topicDir, topicName);

    Topic *topic = loadTopic(topicName);
    topic->setSubscribedUsersCount(topic->getSubscribedUserCount() - 1);
    if (topic->getSubscribedUserCount() <= 0) {
        // remove topicFoo dir
        _fileDataManager->remove(topicDir);
        return;
    }
    std::vector<Message *> *msgs = loadMessages(topicName);
    for (const auto &msg : *msgs) {
        if (msg->getId() > lastConsumedMsgId) {
            msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() - 1);
        }
    }
    saveMessages(topicName, msgs);
    saveTopic(topic);

}

void TopicRepository::initTopicFiles(char *topicName) {
    char *topicDir = Utils::smartstrcat(_topicsDir, topicName);
    unsigned char topicExists = _fileDataManager->exists(_topicsDir, topicName);
    if (topicExists) {
        delete topicDir;
        return;
    }
    Utils::createDirectory(topicDir);
//    _fileDataManager->store(topicDir, "topic", "");
    saveTopic(new Topic(topicName));
    _fileDataManager->store(topicDir, "messages", "");
}

std::vector<Message *> *TopicRepository::loadMessages(char *topicName) {
    char *topicDir = Utils::smartstrcat(_topicsDir, topicName);
    char *msgsJson = _fileDataManager->find(topicDir, "messages");

    using json = nlohmann::json;
    json j = json::parse(msgsJson);

    std::vector<Message *> *msgs = new std::vector<Message *>();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
        if (it.key() == "msg") {
            json msg = it.value().get<std::string>();
            unsigned long msgId = msg.at("id").get<unsigned long>();
            std::string msgValue_s = msg.at("value").get<std::string>();
            unsigned long unconsumed_user_count = msg.at("unconsumed_user_count").get<unsigned long>();

//            long msgId = strtol(msgId_c, NULL, 10);
//            char *msgId_c = Utils::toCharP(&id_s);
            char *msgValue = Utils::toCharP(&msgValue_s);

//            char *unconsumed_user_count_c = Utils::toCharP(&unconsumed_user_count_s);
//            long unconsumed_user_count = strtol(unconsumed_user_count_c, NULL, 10);

            Message *msg_o = new Message(msgId, unconsumed_user_count, msgValue);
            msgs->push_back(msg_o);
        }
    }
    return msgs;
}

