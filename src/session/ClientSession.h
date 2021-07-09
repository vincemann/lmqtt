//
// Created by vince on 09.07.21.
//

#ifndef LMQTT__SERVER_CLIENTSESSION_H
#define LMQTT__SERVER_CLIENTSESSION_H


#include <FileDataManager.h>

class ClientSession {
public:
    ClientSession(char *clientId, char *username, char *password);

    ClientSession();

    char* _clientId;
    char* _username;
    char* _password;

};


#endif //LMQTT__SERVER_CLIENTSESSION_H
