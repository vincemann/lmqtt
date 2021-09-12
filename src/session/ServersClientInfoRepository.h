#ifndef __SESSIONREPOSITORY_H__
#define __SESSIONREPOSITORY_H__

#include <FileDataManager.h>
#include "ServersClientInfo.h"

// my additional comment
class ServersClientInfoRepository{
protected:
FileDataManager* _fileDataManager;
char * serversClientInfoDir;
public:
    void save(ServersClientInfo* session);
    ServersClientInfo* load(char* clientId);

    explicit ServersClientInfoRepository(FileDataManager *fileDataManager);
};

#endif // __SESSIONREPOSITORY_H__