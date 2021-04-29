//
// Created by vince on 22.04.21.
//

#include "PacketHandler.h"
#include "../io/PacketIOManager.h"


PacketHandler::PacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo) : _connectionSession(connectionSession), packetIo(packetIo) {}

void PacketHandler::closeConnection() {
    packetIo->closeConnection();
}
