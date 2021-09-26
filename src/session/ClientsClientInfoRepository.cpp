//
// Created by vince on 09.07.21.
//

#include "ClientsClientInfoRepository.h"
#include "../json.hpp"
#include "../util/Utils.h"
#include "ClientsClientInfo.h"
#include <iostream>
#include <string>
#include <vector>



void ClientsClientInfoRepository::save(ClientsClientInfo *session) {
    // for convenience
    using json = nlohmann::json;
    json j;
    j["clientId"] = session->_clientId;
    j["username"] = session->_username;
    j["password"] = session->_password;
    std::string jsonString = j.dump();
    char *pJsonString = new char[jsonString.length() + 1];
    strcpy(pJsonString, jsonString.c_str());
    std::cout << "json of client session: " << pJsonString << "\n";
    _fileDataManager->store(_clientSessionsDir, session->_clientId, pJsonString);
}

static char * extractJsonValue(nlohmann::json::iterator it){
    std::string s = it.value().get<std::string>();
    std::cout << "found jsonValue: " << s << std::endl;
    char *parsedJsonValue = Utils::toCharP(&s);
    return parsedJsonValue;
}


ClientsClientInfo *ClientsClientInfoRepository::load(char *clientId) {
    std::cout << "clientId gets loaded: " << clientId << "\n";
    char *jsonContent = _fileDataManager->find(_clientSessionsDir, clientId);
    if (jsonContent == nullptr) {
        return nullptr;
    }
    using json = nlohmann::json;
    json j = json::parse(jsonContent);

    ClientsClientInfo *clientSession = new ClientsClientInfo();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
        if (it.key() == "clientId") {
            clientSession->_clientId= extractJsonValue(it);
        } else if (it.key() == "username") {
            clientSession->_username= extractJsonValue(it);
        }else if(it.key() == "password"){
            clientSession->_password= extractJsonValue(it);
        }
    }
    return clientSession;
}

ClientsClientInfoRepository::ClientsClientInfoRepository(FileDataManager *fileDataManager) : _fileDataManager(
        fileDataManager) {
    char* dir = "/.lmqtt/client/info/";
    this->_clientSessionsDir = Utils::createHomeDirectoryChain(dir);
}


