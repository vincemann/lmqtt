




#include "ServerSessionRepository.h"
#include "ServerSession.h"
// #includes <json-c/json.h>
#include "../json.hpp"
#include "../util/Utils.h"
#include <iostream>
#include <string>
#include "FileDataManager.h"


void ServerSessionRepository::save(ServerSession* session)
{
    // for convenience
    using json = nlohmann::json;
    json j;
    // using json j;
    j["clientId"] = 42;
    // j["_subscriptions"] = {session->_subscriptions}
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of server session: " << pJsonString << "\n";
    const char* sessionsDir = "/home/vince/.lmqtt/server/sessions";
    _fileDataManager->store(sessionsDir, session->_clientId, pJsonString);
}

ServerSession* ServerSessionRepository::load(char* clientId)
{
    std::cout << "clientId gets loaded: " << clientId << "\n";
    return nullptr;
}

ServerSessionRepository::ServerSessionRepository(FileDataManager *fileDataManager) : _fileDataManager(
        fileDataManager) {}

