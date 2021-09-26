//
// Created by vince on 26.09.21.
//

#include <InvalidPacketException.h>
#include "ClientDisconnectPacketHandler.h"

void ClientDisconnectPacketHandler::handle(RawPacket *packet) {
    assertSpecificFlagsZero(packet);

    if (packet->getData() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }

    if (packet->getLength() != 0){
        throw InvalidPacketException("Disconnect Packet must not contain data");
    }
    clientConnectionManager->closeConnection();

}

ClientDisconnectPacketHandler::ClientDisconnectPacketHandler(PacketIOManager *packetIo,
                                                             ClientConnectionManager *clientConnectionManager)
        : PacketHandler(packetIo), clientConnectionManager(clientConnectionManager) {}
