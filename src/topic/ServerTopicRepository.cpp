//
// Created by vince on 14.08.21.
//

#include <cstring>
#include <iostream>
#include <Utils.h>
#include "ServerTopicRepository.h"
#include <stdlib.h>
#include "IllegalSessionStateException.h"

#include "../json.hpp"

ServerTopicRepository::ServerTopicRepository(FileDataManager *fileDataManager) : _fileDataManager(fileDataManager) {
    //    _topics = new std::map<Topic *, std::vector<Message *> *>();
    const char *targetDir = "/.lmqtt/server/topics/";
    char *home = getenv("HOME");
    _topicsDir = Utils::smartstrcat(home, targetDir);
    Utils::createHomeDirectoryChain(_topicsDir);
}

void ServerTopicRepository::saveMsg(char *topic_c, char *msg) {

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
        json jsonMsg = {
                        {"id", message->getId()},
                        {"msg_value", message->getMsg()},
                        {"unconsumed_user_count", message->getUnconsumedUserCount()}
        };
        j = {jsonMsg};
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {
                {"id", message->getId()},
                {"msg_value", message->getMsg()},
                {"unconsumed_user_count", message->getUnconsumedUserCount()}
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
//    _fileDataManager->saveMsg(topicDir, "messages", jsonMsgs_c);
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

void ServerTopicRepository::replaceMessages(char *topic, std::vector<Message *> *msgs) {
    using json = nlohmann::json;
    std::vector<json> jsonMsgs = std::vector<json>();

    char *topicDir = Utils::smartstrcat(_topicsDir, topic);


    for (const auto &message : *msgs) {
        json jsonMsg = {
                {"id", message->getId()},
                {"msg_value", message->getMsg()},
                {"unconsumed_user_count", message->getUnconsumedUserCount()}
        };
        jsonMsgs.push_back(jsonMsg);
    }

    json j = jsonMsgs;
    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);
    _fileDataManager->
            store(topicDir,
                  "messages", jsonMsgs_c);
}

void ServerTopicRepository::removeMsg(char *topic, Message *msg) {

}



// expects topic name
Topic *ServerTopicRepository::loadTopic(char *topic) {
    using json = nlohmann::json;

    char *pathToTopicDir = Utils::smartstrcat(_topicsDir, topic);
    //    check file existence
    unsigned char fileExists = _fileDataManager->exists(pathToTopicDir, "topic");
    if (fileExists == 0) {
        throw IllegalSessionStateException("init topic file was not created");
    }

    //    extract values
    char *topicJson = _fileDataManager->find(pathToTopicDir, "topic");
    json j = json::parse(topicJson);
    long subscribedUserCount = j.at("subscribed_users_count").get<unsigned long>();
    long lastMsgIdPublished = j.at("last_msg_id_published").get<unsigned long>();
    std::string s = j.at("topic_value").get<std::string>();
    char *topicValue = Utils::toCharP(&s);

    delete pathToTopicDir;
    delete topicJson;
    return new Topic(lastMsgIdPublished, subscribedUserCount, topicValue);
}



void ServerTopicRepository::saveTopic(Topic *topic) {
    using json = nlohmann::json;
    json j;

    char *topicDir = Utils::smartstrcat(_topicsDir, topic->getTopic());
    j = {
            {"topic_value",            topic->getTopic()},
            {"subscribed_users_count", topic->getSubscribedUserCount()},
            {"last_msg_id_published",  topic->getLastMsgIdPublished()}
    };
    std::string jsonString = j.dump();
    Utils::createDirectory(topicDir);
    _fileDataManager->store(topicDir, "topic", Utils::toCharP(&jsonString));
}


//Message *ServerTopicRepository::loadMessage(Topic *topic, unsigned long msgId) {
//    return nullptr;
//}


std::vector<Message *> *ServerTopicRepository::consumeMessagesStartingFromId(char *topic, unsigned long lastConsumedMsgId) {
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

    for (int i = 0; i < msgs->size(); ++i) {
        auto msg = msgs->at(i);

        if (msg->getId() > lastConsumedMsgId) {
            msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() - 1);
            consumedMsgs->push_back(msg);
            if (msg->getUnconsumedUserCount() > 0){
                updatedMsgs->push_back(msg);
                continue;
            }else{
                // msg will be deleted
                continue;
            }
        }
        updatedMsgs->push_back(msg);
    }
//    for (auto &msg : *msgs) {
//        if (msg->getId() > lastConsumedMsgId) {
//            msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() - 1);
//            consumedMsgs->push_back(msg);
//            updatedMsgs->push_back(msg);
//        }
//        if (msg->getId() <= 0) {
//            updatedMsgs->erase(msg);
//        } else {
//            updatedMsgs->push_back(msg);
//        }
//    }
    // update msges meta data
    replaceMessages(topic, updatedMsgs);
    delete updatedMsgs;
    delete msgs;
    return consumedMsgs;
}

void ServerTopicRepository::subscribe(char *topicName) {
    Topic *topic = loadTopic(topicName);
    topic->setSubscribedUsersCount(topic->getSubscribedUserCount() + 1);
    std::vector<Message *> *msgs = loadMessages(topicName);
    for (const auto &msg : *msgs) {
        msg->setUnconsumedUserCount(msg->getUnconsumedUserCount() + 1);
    }
    replaceMessages(topicName, msgs);
    saveTopic(topic);
}

void ServerTopicRepository::unsubscribe(char *topicName, unsigned long lastConsumedMsgId) {
    char *topicDir = Utils::smartstrcat(_topicsDir, topicName);


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
    replaceMessages(topicName, msgs);
    saveTopic(topic);

}

void ServerTopicRepository::initTopicFiles(char *topicName) {
    char *topicDir = Utils::smartstrcat(_topicsDir, topicName);
    unsigned char topicExists = _fileDataManager->exists(_topicsDir, topicName);
    if (topicExists) {
        delete topicDir;
        return;
    }
    Utils::createDirectory(topicDir);
//    _fileDataManager->saveMsg(topicDir, "topic", "");
    saveTopic(new Topic(topicName));
    _fileDataManager->store(topicDir, "messages", "");
}

std::vector<Message *> *ServerTopicRepository::loadMessages(char *topicName) {
    char *topicDir = Utils::smartstrcat(_topicsDir, topicName);
    char *msgsJson = _fileDataManager->find(topicDir, "messages");

    using json = nlohmann::json;
    json j = json::parse(msgsJson);

    std::vector<Message *> *msgs = new std::vector<Message *>();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        unsigned long msgId = it.value().at("id").get<unsigned long>();
        unsigned long unconsumed_user_count = it.value().at("unconsumed_user_count").get<unsigned long>();
        std::string s = it.value().at("msg_value").get<std::string>();
        char *msgValue = Utils::toCharP(&s);
        Message *msg_o = new Message(msgId, unconsumed_user_count, msgValue);
        msgs->push_back(msg_o);
    }
    return msgs;
}

