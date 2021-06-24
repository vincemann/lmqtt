//
// Created by vince on 06.04.21.
//


#ifndef LMQTT__SERVER_PARSEREXCEPTION_H
#define LMQTT__SERVER_PARSEREXCEPTION_H

#include <exception>
#include "../../MsgException.h"

class PacketIOException :  public MsgException {
public:
    explicit PacketIOException(const char* msg);
    const char * what () const noexcept;
};

#endif //LMQTT__SERVER_PARSEREXCEPTION_H
