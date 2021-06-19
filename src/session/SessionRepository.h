#ifndef __SESSIONREPOSITORY_H__
#define __SESSIONREPOSITORY_H__

#include "Session.h"
#include "../files/FileDataManager.h"

class SessionRepository{
private:
FileDataManager* _fileDataManager;
public:
    void save(Session* session, char* id);
    Session* load(char* id);
};

#endif // __SESSIONREPOSITORY_H__