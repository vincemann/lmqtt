//
// Created by vince on 09.07.21.
//

#ifndef LMQTT__SERVER_CLIENTSCLIENTINFO_H
#define LMQTT__SERVER_CLIENTSCLIENTINFO_H


#include <FileDataManager.h>

class ClientsClientInfo {
public:
    ClientsClientInfo(char *clientId, char *username, char *password);

    ClientsClientInfo();

    char* _clientId;
    char* _username;
    char* _password;

};


#endif //LMQTT__SERVER_CLIENTSCLIENTINFO_H
