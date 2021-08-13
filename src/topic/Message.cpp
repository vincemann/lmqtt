//
// Created by vince on 14.08.21.
//

#include "Message.h"

Message::Message(long id, int unconsumedUserCount, char *msg) : _id(id), _unconsumed_user_count(unconsumedUserCount),
                                                                _msg(msg) {}

long Message::getId() const {
    return _id;
}

int Message::getUnconsumedUserCount() const {
    return _unconsumed_user_count;
}

char *Message::getMsg() const {
    return _msg;
}
