//
// Created by vince on 25.09.21.
//

#ifndef LMQTT__SERVER_CLIENTTOPICREPOSITORY_H
#define LMQTT__SERVER_CLIENTTOPICREPOSITORY_H


#include <FileDataManager.h>

class ClientTopicRepository {
    char* clientId;
protected:
    char* _topicsDir;
    FileDataManager *fileDataManager;
public:
    ClientTopicRepository(FileDataManager *fileDataManager);

    void saveTopic( char* topic);

    virtual void saveMsg( char* topic, char* msg);
    bool topicExists( char *topic);

    virtual void initTopicsDir(char* clientId);

};


#endif //LMQTT__SERVER_CLIENTTOPICREPOSITORY_H
