//
// Created by vince on 25.09.21.
//

#include <cstring>
#include <Utils.h>
#include "ClientTopicRepository.h"
#include "../json.hpp"
#include "ClientMessageContainer.h"

void ClientTopicRepository::saveTopic(char *topic) {
    // store dir for topic
    char *topicsDir = Utils::smartstrcat(_topicsDir, topic);
    Utils::createDirectory(topicsDir);
    fileDataManager->store(topicsDir, "messages", "");
    delete topicsDir;
}

void ClientTopicRepository::saveMsg(char *topic, char *msg) {

    char *topicDir = Utils::smartstrcat(_topicsDir, topic);
    char *msgsJson = fileDataManager->find(topicDir, "messages");

    ClientMessageContainer *clientMessageContainer = new ClientMessageContainer(msg);
    using json = nlohmann::json;
    json j;
    if (strlen(msgsJson) == 0) {
        json jsonMsg = {
                {"msg", clientMessageContainer->getMsg()},
                {"id", clientMessageContainer->getId()}

        };
        j = {jsonMsg};
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {
                {"msg", clientMessageContainer->getMsg()},
                {"id", clientMessageContainer->getId()}
        };
        j.push_back(jsonMsg);
    }

    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);

    fileDataManager->store(topicDir, "messages", jsonMsgs_c);
}

ClientTopicRepository::ClientTopicRepository(FileDataManager *fileDataManager) : fileDataManager(fileDataManager) {
    char* dir = "/.lmqtt/client/topics/";
    this->_topicsDir = Utils::createHomeDirectoryChain(dir);
}

bool ClientTopicRepository::topicExists(char* topic) {
    return fileDataManager->exists(_topicsDir,topic);
}
