#ifndef __SESSIONREPOSITORY_H__
#define __SESSIONREPOSITORY_H__

#include <FileDataManager.h>
#include "ServerSession.h"


class ServerSessionRepository{
private:
FileDataManager* _fileDataManager;
public:
    void save(ServerSession* session);
    ServerSession* load(char* clientId);

    ServerSessionRepository(FileDataManager *fileDataManager);
};

#endif // __SESSIONREPOSITORY_H__