//
// Created by vince on 25.10.21.
//

#include "ClientQosTopicRepository.h"

void QosTopicRepository::initTopicsDir(char *clientId) {
    char* dir = Utils::smartstrcat("/.lmqtt/client/",clientId);
    dir = Utils::smartstrcat(dir,"/retransmit/");
    this->retransmitDir = Utils::createHomeDirectoryChain(dir);
    if (fileDataManager->exists(retransmitDir, "messages") == 0){
        fileDataManager->store(retransmitDir, "messages", "[]");
    }
    delete dir;
}

void ClientQosTopicRepository::initTopicsDir(char *clientId) {
    QosTopicRepository::initTopicsDir(clientId);
}

ClientQosTopicRepository::ClientQosTopicRepository(FileDataManager *fileDataManager) : QosTopicRepository(
        fileDataManager) {}
