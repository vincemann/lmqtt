


#include "ServerSessionRepository.h"
#include "ServerSession.h"
#include "../json.hpp"
#include "../util/Utils.h"
#include <iostream>
#include <string>
#include "FileDataManager.h"



void ServerSessionRepository::save(ServerSession *session) {
    // for convenience
    using json = nlohmann::json;
    json j;
    j["clientId"] = session->_clientId;
    j["subscriptions"] = *session->_qos_subscriptions;
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of server session: " << pJsonString << "\n";
    _fileDataManager->store(_serverSessionsDir, session->_clientId, pJsonString);
}

ServerSession *ServerSessionRepository::load(char *clientId) {
    std::cout << "clientId gets loaded: " << clientId << "\n";
    char *jsonContent = _fileDataManager->find(_serverSessionsDir, clientId);
    if (jsonContent == nullptr) {
        return nullptr;
    }
    using json = nlohmann::json;
    json j = json::parse(jsonContent);
//    auto parsedClientId = j.find("clientId")

    // special iterator member functions for objects
    // todo replace iterator with find method maybe
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
                serverSession->_qos_subscriptions->push_back(parsedSubscription);
            }
        }
    }
    return serverSession;
}

ServerSessionRepository::ServerSessionRepository(FileDataManager *fileDataManager) : _fileDataManager(
        fileDataManager) {
    const char* targetDir = "/.lmqtt/server/sessions";
    char* home = getenv("HOME");
    _serverSessionsDir = Utils::smartstrcat(home,targetDir);
    Utils::createHomeDirectoryChain(_serverSessionsDir);
}

