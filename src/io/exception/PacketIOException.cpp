//
// Created by vince on 06.04.21.
//

#include "PacketIOException.h"


PacketIOException::PacketIOException(const char *msg) : MsgException(msg) {

}

const char *PacketIOException::what() const noexcept {
    return MsgException::what();
}
