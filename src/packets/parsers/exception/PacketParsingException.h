//
// Created by vince on 08.04.21.
//


#ifndef LMQTT__SERVER_PACKETPARSINGEXCEPTION_H
#define LMQTT__SERVER_PACKETPARSINGEXCEPTION_H

#include <exception>
#include "../../../MsgException.h"


class PacketParsingException  :  public MsgException {
public:
    explicit PacketParsingException(const char* msg);
    const char * what () const noexcept;
};

#endif //LMQTT__SERVER_PACKETPARSINGEXCEPTION_H
