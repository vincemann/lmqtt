//
// Created by vince on 22.04.21.
//

#include "PacketHandler.h"
#include "../io/PacketIOManager.h"


PacketHandler::PacketHandler(Session *session, PacketIOManager *packetIo) : _session(session), packetIo(packetIo) {}
