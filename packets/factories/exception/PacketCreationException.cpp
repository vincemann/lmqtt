//
// Created by vince on 08.04.21.
//


#include "PacketCreationException.h"

PacketParsingException::PacketCreationException(const char *msg) {
    _msg=msg;
}

const char *PacketParsingException::what() const throw() {
    return _msg;
}
