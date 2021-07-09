//
// Created by vince on 01.05.21.
//

#include "ClientConnection.h"

ClientConnection::ClientConnection() {}

ClientConnection::ClientConnection(ConnectPacket *connectPacket) : _connectPacket(connectPacket) {}

ConnectPacket *ClientConnection::getConnectPacket() const {
    return _connectPacket;
}
