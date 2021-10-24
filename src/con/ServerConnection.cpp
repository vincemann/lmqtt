//
// Created by vince on 01.05.21.
//

#include "ServerConnection.h"
#include "ServersClientInfoRepository.h"



ServersClientInfo *ServerConnection::loadServersClientInfo() const {
    return serversClientInfoRepository->load(serversClientInfo->getClientId());
}

void ServerConnection::setServersClientInfo(ServersClientInfo *serversClientInfo) {
    ServerConnection::serversClientInfo = serversClientInfo;
}

ServerConnection::ServerConnection(ServersClientInfoRepository *serversClientInfoRepository)
        : serversClientInfoRepository(serversClientInfoRepository) {}


