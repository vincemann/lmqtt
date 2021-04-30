//
// Created by vince on 01.05.21.
//

#include "ConnectAckPacketHandler.h"

ConnectAckPacketHandler::ConnectAckPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo)
        : PacketHandler(connectionSession, packetIo) {}

void ConnectAckPacketHandler::handle(RawPacket *packet) {
    printf("handling connect ack packet\n");
}
