//
// Created by vince on 30.09.21.
//

#include <Utils.h>
#include "QosTopicRepository.h"
#include "../json.hpp"
#include "QosMessageContainer.h"


void QosTopicRepository::saveMsg(QosMessageContainer *msg) {
    char *msgsJson = fileDataManager->find(retransmitDir, "messages");

    using json = nlohmann::json;
    json j;
    if (strlen(msgsJson) == 0) {
        json jsonMsg = {
                {"value", msg->getValue()},
                {"packet-id", msg->getId()},
                {"qos", msg->getQos()},
                {"topic", msg->getTopic()}

        };
        j = {jsonMsg};
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {
                {"value", msg->getValue()},
                {"packet-id", msg->getId()},
                {"qos", msg->getQos()},
                {"topic", msg->getTopic()}
        };
        j.push_back(jsonMsg);
    }

    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);

    fileDataManager->store(retransmitDir, "messages", jsonMsgs_c);
}

std::vector<QosMessageContainer*> *QosTopicRepository::loadMessages() {
    char *msgsJson = fileDataManager->find(retransmitDir, "messages");
    std::vector<QosMessageContainer *> *msgs = new std::vector<QosMessageContainer*>();

    using json = nlohmann::json;
    if (strlen(msgsJson) == 0 ){
        return msgs;
    }
    json j = json::parse(msgsJson);

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        int id = it.value().at("packet-id").get<int>();
        unsigned char qos = it.value().at("qos").get<unsigned char>();
        std::string value_s = it.value().at("value").get<std::string>();
        std::string topic_s = it.value().at("topic").get<std::string>();
        char *value = Utils::toCharP(&value_s);
        char *topic = Utils::toCharP(&topic_s);

        QosMessageContainer* msg = new QosMessageContainer(value, qos, id, topic);
        msgs->push_back(msg);
    }
    return msgs;
}


void QosTopicRepository::replaceMessages(std::vector<QosMessageContainer *> *msgs) {
    using json = nlohmann::json;
    std::vector<json> jsonMsgs = std::vector<json>();


    for (const auto &msg : *msgs) {
        json jsonMsg = {
                {"value", msg->getValue()},
                {"packet-id", msg->getId()},
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

QosTopicRepository::QosTopicRepository(FileDataManager *fileDataManager)
        :  fileDataManager(fileDataManager) {}


