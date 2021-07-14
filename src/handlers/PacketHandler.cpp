//
// Created by vince on 22.04.21.
//

#include <InvalidPacketException.h>
#include "PacketHandler.h"
#include "../io/PacketIOManager.h"


PacketHandler::PacketHandler(PacketIOManager *packetIo) : _packetIo(packetIo){

}



PacketHandler::~PacketHandler() {

}

void PacketHandler::assertSpecificFlagsZero(RawPacket* packet) {
    if (packet->getSpecificFlags() != 0){
        throw InvalidPacketException("Specific Flags must be 0 (reserved)");
    }
}


//PacketHandler::~PacketHandler() {
//
//}
