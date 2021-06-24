//
// Created by vince on 22.04.21.
//

#include "PacketHandler.h"
#include "../io/PacketIOManager.h"


PacketHandler::PacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo) : _connectionSession(connectionSession), _packetIo(packetIo) {}

