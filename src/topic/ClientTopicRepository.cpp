//
// Created by vince on 25.09.21.
//

#include <cstring>
#include <Utils.h>
#include "ClientTopicRepository.h"
#include "../json.hpp"
#include "QosMessageContainer.h"

void ClientTopicRepository::saveTopic(char *topic) {
    // store dir for topic
    char *topicsDir = Utils::smartstrcat(_topicsDir, topic);
    Utils::createDirectory(topicsDir);
    if (fileDataManager->exists(topicsDir,"messages") == 0 ){
        fileDataManager->store(topicsDir, "messages", "[]");
    }
    delete topicsDir;
}

void ClientTopicRepository::saveMsg(char *topic, char *msg) {

    char *topicDir = Utils::smartstrcat(_topicsDir, topic);
    char *msgsJson = fileDataManager->find(topicDir, "messages");

    using json = nlohmann::json;
    json j;
    if (strlen(msgsJson) == 0) {
        json jsonMsg = {
                {"value", msg},

        };
        j = {jsonMsg};
    } else {
        j = json::parse(msgsJson);
        json jsonMsg = {
                {"value", msg},
        };
        j.push_back(jsonMsg);
    }

    std::string jsonMsgsString = j.dump();
    char *jsonMsgs_c = Utils::toCharP(&jsonMsgsString);

    fileDataManager->store(topicDir, "messages", jsonMsgs_c);
}

ClientTopicRepository::ClientTopicRepository(FileDataManager *fileDataManager)
        : fileDataManager(fileDataManager) {
}

bool ClientTopicRepository::topicExists(char* topic) {
    return fileDataManager->exists(_topicsDir,topic);
}

void ClientTopicRepository::initTopicsDir(char *clientId) {
    char* dir = Utils::smartstrcat("/.lmqtt/client/",clientId);
    dir = Utils::smartstrcat(dir,"/topics/");
    this->_topicsDir = Utils::createHomeDirectoryChain(dir);
    delete dir;
}
