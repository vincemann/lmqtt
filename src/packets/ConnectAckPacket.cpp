//
// Created by vince on 30.04.21.
//

#include "ConnectAckPacket.h"
#include "../RawPacket.h"


ConnectAckPacket::ConnectAckPacket(RawPacket *rawPacket, unsigned char sessionPresent, unsigned char returnCode)
: RawPacket(rawPacket), _sessionPresent(
        sessionPresent), _returnCode(returnCode) {}

unsigned char ConnectAckPacket::getSessionPresent() const {
    return _sessionPresent;
}

unsigned char ConnectAckPacket::getReturnCode() const {
    return _returnCode;
}
