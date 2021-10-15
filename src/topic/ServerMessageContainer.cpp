//
// Created by vince on 14.08.21.
//

#include "ServerMessageContainer.h"

ServerMessageContainer::ServerMessageContainer(int id, int unconsumedUserCount, char *msg) : _id(id), _unconsumed_user_count(unconsumedUserCount),
                                                                                                                 _msg(msg) {}

int ServerMessageContainer::getId() const {
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

void ServerMessageContainer::setId(int id) {
    _id = id;
}

void ServerMessageContainer::setUnconsumedUserCount(int unconsumedUserCount) {
    _unconsumed_user_count = unconsumedUserCount;
}
