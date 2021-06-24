//
// Created by vince on 08.04.21.
//


#include "PacketParsingException.h"


PacketParsingException::PacketParsingException(const char *msg) : MsgException(msg) {

}

const char *PacketParsingException::what() const noexcept {
    return MsgException::what();
}
