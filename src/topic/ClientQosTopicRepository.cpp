//
// Created by vince on 30.09.21.
//

#include <Utils.h>
#include "ClientQosTopicRepository.h"
#include "../json.hpp"
#include "ClientQosMessageContainer.h"

void ClientQosTopicRepository::initTopicsDir(char *clientId) {
    char* dir = Utils::smartstrcat("/.lmqtt/client/",clientId);
    dir = Utils::smartstrcat(dir,"/retransmit/");
    this->retransmitDir = Utils::createHomeDirectoryChain(dir);
    if (! fileDataManager->exists(retransmitDir, "messages")){
        fileDataManager->store(retransmitDir, "messages", "[]");
    }
    delete dir;
}

void ClientQosTopicRepository::saveMsg(ClientQosMessageContainer *msg) {
    char *topicDir = Utils::smartstrcat(retransmitDir, msg->getTopic());
    char *msgsJson = fileDataManager->find(topicDir, "messages");

    using json = nlohmann::json;
    json j;
    if (strlen(msgsJson) == 0) {
        json jsonMsg = {
                {"value", msg->getValue()},
                {"id", msg->getId()},
                {"qos", msg->getQos()},
                {"topic", msg->getTopic()}

        };
        j = {jsonMsg};
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {
                {"value", msg->getValue()},
                {"id", msg->getId()},
                {"qos", msg->getQos()},
                {"topic", msg->getTopic()}
        };
        j.push_back(jsonMsg);
    }

    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);

    fileDataManager->store(topicDir, "messages", jsonMsgs_c);
}

std::vector<ClientQosMessageContainer*> *ClientQosTopicRepository::loadMessages() {
    char *msgsJson = fileDataManager->find(retransmitDir, "messages");
    std::vector<ClientQosMessageContainer *> *msgs = new std::vector<ClientQosMessageContainer*>();

    using json = nlohmann::json;
    if (strlen(msgsJson) == 0 ){
        return msgs;
    }
    json j = json::parse(msgsJson);

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        unsigned long id = it.value().at("id").get<unsigned long>();
        unsigned char qos = it.value().at("qos").get<unsigned char>();
        std::string value_s = it.value().at("value").get<std::string>();
        std::string topic_s = it.value().at("topic").get<std::string>();
        char *value = Utils::toCharP(&value_s);
        char *topic = Utils::toCharP(&topic_s);

        ClientQosMessageContainer* msg = new ClientQosMessageContainer(value, qos, id, topic);
        msgs->push_back(msg);
    }
    return msgs;
}


void ClientQosTopicRepository::replaceMessages(std::vector<ClientQosMessageContainer *> *msgs) {
    using json = nlohmann::json;
    std::vector<json> jsonMsgs = std::vector<json>();


    for (const auto &msg : *msgs) {
        json jsonMsg = {
                {"value", msg->getValue()},
                {"id", msg->getId()},
                {"qos", msg->getQos()},
                {"topic", msg->getTopic()}

        };
        jsonMsgs.push_back(jsonMsg);
    }

    json j = jsonMsgs;
    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);
    fileDataManager->
            store(retransmitDir,
                  "messages", jsonMsgs_c);
}


