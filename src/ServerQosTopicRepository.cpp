//
// Created by vince on 25.10.21.
//

#include <Utils.h>
#include "ServerQosTopicRepository.h"

void ServerQosTopicRepository::initTopicsDir(char *clientId) {
    char* dir = Utils::smartstrcat("/.lmqtt/server/",clientId);
    dir = Utils::smartstrcat(dir,"/retransmit/");
    this->retransmitDir = Utils::createHomeDirectoryChain(dir);
    if (fileDataManager->exists(retransmitDir, "messages") == 0){
        fileDataManager->store(retransmitDir, "messages", "[]");
    }
    delete dir;
}

ServerQosTopicRepository::ServerQosTopicRepository(FileDataManager *fileDataManager) : QosTopicRepository(
        fileDataManager) {}
