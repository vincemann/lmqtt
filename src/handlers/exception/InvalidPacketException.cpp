//
// Created by vince on 29.04.21.
//

#include "InvalidPacketException.h"


InvalidPacketException::InvalidPacketException(const char *msg) : MsgException(msg) {

}

const char *InvalidPacketException::what() const noexcept {
    return MsgException::what();
}
