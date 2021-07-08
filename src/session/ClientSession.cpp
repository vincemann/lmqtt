//
// Created by vince on 09.07.21.
//

#include "ClientSession.h"

ClientSession::ClientSession(char *clientId, char *username, char *password)
        : _clientId(clientId), _username(username),
          _password(password) {}

ClientSession::ClientSession() {}
