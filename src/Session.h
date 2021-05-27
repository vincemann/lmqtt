//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

# define BASE_DIR "~/.lmqtt"
# define SESSION_DIR BASEDIR+"/sessions"

class Session {
public:
    char * _clientId;

};


#endif //LMQTT__SERVER_SESSION_H
