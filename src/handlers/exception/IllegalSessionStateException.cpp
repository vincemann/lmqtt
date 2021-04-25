//
// Created by vince on 08.04.21.
//

#include "IllegalSessionStateException.h"

IllegalSessionStateException::IllegalSessionStateException(const char *msg) {
    _msg=msg;
}

const char *IllegalSessionStateException::what() const throw() {
    return _msg;
}