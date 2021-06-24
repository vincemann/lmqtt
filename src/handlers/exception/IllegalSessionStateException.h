//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
#define LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
#include <exception>
#include "../../MsgException.h"

class IllegalSessionStateException : public MsgException {
public:
    explicit IllegalSessionStateException(const char* msg);
    const char * what () const noexcept;
};

#endif //LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
