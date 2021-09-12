//
// Created by vince on 01.05.21.
//

#include "ServerConnection.h"

ServerConnection::ServerConnection() : Connection() {}


ServerConnection::ServerConnection(ServersClientInfo *serverSession) : serversClientInfo(serverSession) {}
