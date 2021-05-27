//
// Created by vince on 01.05.21.
//

#include "ConnectAckPacketHandler.h"
#include "ConnectAckPacket.h"
#include "InvalidPacketException.h"
#include "IllegalSessionStateException.h"

ConnectAckPacketHandler::ConnectAckPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo)
        : PacketHandler(connectionSession, packetIo) {}

void ConnectAckPacketHandler::handle(RawPacket *rawPacket) {
    printf("handling connect ack packet\n");
    ConnectAckPacket* packet = static_cast<ConnectAckPacket*>(rawPacket);
    unsigned char retCode = packet->getReturnCode();
    switch (retCode)
    {
    case 0:
        /* code */
        printf("Connection Accepted\n");
        break;
     case 1:
        throw new InvalidPacketException("Connection Refused, unacceptable protocol version");
        break;
     case 2:
        throw new InvalidPacketException("Connection Refused, identifier rejected");
        break;
    case 3:
        throw new InvalidPacketException("Connection Refused, Server unavailable");
        break;
    case 4:
        throw new InvalidPacketException("Connection Refused, bad user name or password");
        break;
    case 5:
        throw new InvalidPacketException("Connection Refused, not authorized");
        break;
    default:
        throw new InvalidPacketException("Connection Refused, unknown error");
        break;
    }

    // todo implement session state
}
