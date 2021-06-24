//
// Created by vince on 08.04.21.
//


#include "PacketCreationException.h"


PacketCreationException::PacketCreationException(const char *msg) : MsgException(msg) {

}

const char *PacketCreationException::what() const noexcept {
    return MsgException::what();
}
