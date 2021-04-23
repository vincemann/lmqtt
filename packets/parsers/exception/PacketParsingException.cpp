//
// Created by vince on 08.04.21.
//


#include "PacketParsingException.h"

PacketParsingException::PacketParsingException(const char *msg) {
    _msg=msg;
}

const char *PacketParsingException::what() const throw() {
    return _msg;
}
