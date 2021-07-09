//
// Created by vince on 09.07.21.
//

#ifndef LMQTT__SERVER_CLIENTSESSIONREPOSITORY_H
#define LMQTT__SERVER_CLIENTSESSIONREPOSITORY_H

#include "ClientSession.h"



class ClientSessionRepository {
public:
    FileDataManager* _fileDataManager;

    ClientSessionRepository(FileDataManager *fileDataManager);

    void save(ClientSession *session);
    ClientSession *load(char *clientId);
    char *_clientSessionsDir;
};


#endif //LMQTT__SERVER_CLIENTSESSIONREPOSITORY_H
