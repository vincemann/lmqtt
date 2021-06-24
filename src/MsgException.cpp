//
// Created by vince on 24.06.21.
//

#include "MsgException.h"


MsgException::MsgException(const char *msg) {
    _msg=msg;
}

const char *MsgException::what() const throw() {
    return _msg;
}
