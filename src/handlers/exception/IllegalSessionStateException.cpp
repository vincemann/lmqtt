//
// Created by vince on 08.04.21.
//

#include "IllegalSessionStateException.h"

IllegalSessionStateException::IllegalSessionStateException(const char *msg) : MsgException(msg) {

}

const char *IllegalSessionStateException::what() const noexcept {
    return MsgException::what();
}
