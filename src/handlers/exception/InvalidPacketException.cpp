//
// Created by vince on 29.04.21.
//

#include "InvalidPacketException.h"

InvalidPacketException::InvalidPacketException(const char *msg) {
    _msg=msg;
}

const char *InvalidPacketException::what() const throw() {
    return _msg;
}
