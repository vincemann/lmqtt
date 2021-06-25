


#include "ServerSessionRepository.h"
#include "ServerSession.h"
// #includes <json-c/json.h>
#include "../json.hpp"
#include "../util/Utils.h"
#include <iostream>
#include <string>
#include "FileDataManager.h"


const char *SESSIONS_DIR = "/home/vince/.lmqtt/server/sessions";

void ServerSessionRepository::save(ServerSession *session) {
    // for convenience
    using json = nlohmann::json;
    json j;
    j["clientId"] = session->_clientId;
    j["subscriptions"] = *session->_subscriptions;
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of server session: " << pJsonString << "\n";
    _fileDataManager->store(SESSIONS_DIR, session->_clientId, pJsonString);
}

ServerSession *ServerSessionRepository::load(char *clientId) {
    std::cout << "clientId gets loaded: " << clientId << "\n";
    char *jsonContent = _fileDataManager->find(SESSIONS_DIR, clientId);
    if (jsonContent == nullptr) {
        return nullptr;
    }
    using json = nlohmann::json;
    json j = json::parse(jsonContent);
//    auto parsedClientId = j.find("clientId")

    // special iterator member functions for objects
    ServerSession *serverSession = 0;
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
        if (it.key() == "clientId") {
            std::string s = it.value().get<std::string>();
            std::cout << "found clientId: " << s << std::endl;
            char *parsedClientId = Utils::toCharP(&s);
            serverSession = new ServerSession(parsedClientId);
        } else if (it.key() == "subscriptions") {
            // via value() call i can get the json child object and thus move down the hierachry
            // el should be a json object as well
            for (auto& el : it.value().items()){
                std::string s = el.value().get<std::string>();
                char *parsedSubscription = Utils::toCharP(&s);
                serverSession->_subscriptions->push_back(parsedSubscription);
            }
        }
    }
    return serverSession;
}

ServerSessionRepository::ServerSessionRepository(FileDataManager *fileDataManager) : _fileDataManager(
        fileDataManager) {}

