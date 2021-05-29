//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H


namespace SessionFiles{
    char* BASE_DIR = "~/.lmqtt";
    char* SESSION_DIR = *BASE_DIR + "/sessions";
};


class Session {
public:
    char * _clientId;

};


#endif //LMQTT__SERVER_SESSION_H
