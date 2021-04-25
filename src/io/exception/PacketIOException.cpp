//
// Created by vince on 06.04.21.
//

#include "PacketIOException.h"

PacketIOException::PacketIOException(const char *msg) {
    _msg=msg;
}

const char *PacketIOException::what() const throw() {
    return _msg;
}
