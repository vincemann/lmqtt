#ifndef __SESSIONREPOSITORY_H__
#define __SESSIONREPOSITORY_H__

#include <FileDataManager.h>
#include "ServerSession.h"


class ServerSessionRepository{
protected:
FileDataManager* _fileDataManager;
char * _serverSessionsDir;
public:
    void save(ServerSession* session);
    ServerSession* load(char* clientId);

    explicit ServerSessionRepository(FileDataManager *fileDataManager);
};

#endif // __SESSIONREPOSITORY_H__