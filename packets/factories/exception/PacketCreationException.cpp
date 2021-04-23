//
// Created by vince on 08.04.21.
//


#include "PacketCreationException.h"

PacketCreationException::PacketCreationException(const char *msg) {
    _msg=msg;
}

const char *PacketCreationException::what() const throw() {
    return _msg;
}
