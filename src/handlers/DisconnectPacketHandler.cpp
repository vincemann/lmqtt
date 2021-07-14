//
// Created by vince on 14.07.21.
//

#include <InvalidPacketException.h>
#include "DisconnectPacketHandler.h"

void DisconnectPacketHandler::handle(RawPacket *packet) {

    assertSpecificFlagsZero(packet);

    if (packet->getData() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }

    if (packet->getLength() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }
    this->_connectionManager->disconnectClient();


}

DisconnectPacketHandler::DisconnectPacketHandler(PacketIOManager *packetIo, ConnectionManager *connectionManager)
        : PacketHandler(packetIo), _connectionManager(connectionManager) {}
