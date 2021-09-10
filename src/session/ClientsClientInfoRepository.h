//
// Created by vince on 09.07.21.
//

#ifndef LMQTT__SERVER_CLIENTSCLIENTINFOREPOSITORY_H
#define LMQTT__SERVER_CLIENTSCLIENTINFOREPOSITORY_H

#include "ClientsClientInfo.h"



class ClientsClientInfoRepository {
public:
    FileDataManager* _fileDataManager;

    ClientsClientInfoRepository(FileDataManager *fileDataManager);

    void save(ClientsClientInfo *session);
    ClientsClientInfo *load(char *clientId);
    /**
     * load first client session file found
     * @return
     */
    char *_clientSessionsDir;
};


#endif //LMQTT__SERVER_CLIENTSCLIENTINFOREPOSITORY_H
