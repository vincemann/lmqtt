//
// Created by vince on 08.04.21.
//


#ifndef LMQTT__SERVER_PACKETCREATIONEXCEPTION_H
#define LMQTT__SERVER_PACKETCREATIONEXCEPTION_H

#include <exception>
#include "../../../MsgException.h"


class PacketCreationException :  public MsgException {
public:
    explicit PacketCreationException(const char* msg);
    const char * what () const noexcept;
};

#endif //LMQTT__SERVER_PACKETCREATIONEXCEPTION_H
