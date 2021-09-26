//
// Created by vince on 14.07.21.
//

#include <InvalidPacketException.h>
#include "ServerDisconnectPacketHandler.h"

void ServerDisconnectPacketHandler::handle(RawPacket *packet) {

    assertSpecificFlagsZero(packet);

    if (packet->getData() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }

    if (packet->getLength() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }
    this->_connectionManager->disconnectClient();


}

ServerDisconnectPacketHandler::ServerDisconnectPacketHandler(PacketIOManager *packetIo, ServerConnectionManager *connectionManager)
        : PacketHandler(packetIo), _connectionManager(connectionManager) {}
