//
// Created by vince on 09.07.21.
//

#include "ClientSessionRepository.h"
#include "../json.hpp"
#include "../util/Utils.h"
#include "ClientSession.h"
#include <iostream>
#include <string>

const char *SESSIONS_DIR = "/home/vince/.lmqtt/client/sessions";


void ClientSessionRepository::save(ClientSession *session) {
    // for convenience
    using json = nlohmann::json;
    json j;
    j["clientId"] = session->_clientId;
    j["username"] = *session->_username;
    j["password"] = *session->_password;
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of server session: " << pJsonString << "\n";
    _fileDataManager->store(SESSIONS_DIR, session->_clientId, pJsonString);
}

static char * extractJsonValue(nlohmann::json::iterator it){
    std::string s = it.value().get<std::string>();
    std::cout << "found jsonValue: " << s << std::endl;
    char *parsedJsonValue = Utils::toCharP(&s);
    return parsedJsonValue;
}


ClientSession *ClientSessionRepository::load(char *clientId) {
    std::cout << "clientId gets loaded: " << clientId << "\n";
    char *jsonContent = _fileDataManager->find(SESSIONS_DIR, clientId);
    if (jsonContent == nullptr) {
        return nullptr;
    }
    using json = nlohmann::json;
    json j = json::parse(jsonContent);
    //    auto parsedClientId = j.find("clientId")

    // special iterator member functions for objects
    // todo replace iterator with find method maybe
    ClientSession *clientSession = new ClientSession();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
        if (it.key() == "clientId") {
            clientSession->_clientId= extractJsonValue(it);
        } else if (it.key() == "username") {
            clientSession->_username= extractJsonValue(it);
        }else if(it.key() == "password")
            clientSession->_password= extractJsonValue(it);
        }
    }

ClientSessionRepository::ClientSessionRepository(FileDataManager *fileDataManager) : _fileDataManager(
        fileDataManager) {}
