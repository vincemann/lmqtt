//
// Created by vince on 29.04.21.
//

#ifndef LMQTT__SERVER_INVALIDPACKETEXCEPTION_H
#define LMQTT__SERVER_INVALIDPACKETEXCEPTION_H

#include <exception>
#include "../../MsgException.h"

class InvalidPacketException :  public MsgException {
public:
    explicit InvalidPacketException(const char* msg);
    const char * what () const noexcept;
};


#endif //LMQTT__SERVER_INVALIDPACKETEXCEPTION_H
