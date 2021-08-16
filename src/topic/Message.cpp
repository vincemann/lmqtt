//
// Created by vince on 14.08.21.
//

#include "Message.h"

Message::Message(unsigned long id, unsigned long unconsumedUserCount, char *msg) : _id(id), _unconsumed_user_count(unconsumedUserCount),
                                                                _msg(msg) {}

unsigned long Message::getId() const {
    return _id;
}

int Message::getUnconsumedUserCount() const {
    return _unconsumed_user_count;
}

char *Message::getMsg() const {
    return _msg;
}

Message::Message(char *msg) : _msg(msg){
    _unconsumed_user_count=1;
    _id = 0;
}


void Message::setMsg(char *msg) {
    _msg = msg;
}

void Message::setId(unsigned long id) {
    _id = id;
}

void Message::setUnconsumedUserCount(unsigned long unconsumedUserCount) {
    _unconsumed_user_count = unconsumedUserCount;
}
