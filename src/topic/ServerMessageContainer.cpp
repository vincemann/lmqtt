//
// Created by vince on 14.08.21.
//

#include "ServerMessageContainer.h"

ServerMessageContainer::ServerMessageContainer(unsigned long id, unsigned long unconsumedUserCount, char *msg) : _id(id), _unconsumed_user_count(unconsumedUserCount),
                                                                                                                 _msg(msg) {}

unsigned long ServerMessageContainer::getId() const {
    return _id;
}

int ServerMessageContainer::getUnconsumedUserCount() const {
    return _unconsumed_user_count;
}

char *ServerMessageContainer::getMsg() const {
    return _msg;
}

ServerMessageContainer::ServerMessageContainer(char *msg) : _msg(msg){
    _unconsumed_user_count=1;
    _id = 0;
}


void ServerMessageContainer::setMsg(char *msg) {
    _msg = msg;
}

void ServerMessageContainer::setId(unsigned long id) {
    _id = id;
}

void ServerMessageContainer::setUnconsumedUserCount(unsigned long unconsumedUserCount) {
    _unconsumed_user_count = unconsumedUserCount;
}
