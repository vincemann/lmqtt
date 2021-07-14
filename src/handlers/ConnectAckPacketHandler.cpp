//
// Created by vince on 01.05.21.
//

#include "ConnectAckPacketHandler.h"
#include "ConnectAckPacket.h"
#include "InvalidPacketException.h"
#include "IllegalSessionStateException.h"

ConnectAckPacketHandler::ConnectAckPacketHandler(PacketIOManager *packetIo,
                                                 ClientSessionRepository *clientSessionRepository,
                                                 ClientConnection *clientConnectionSession)
        : PacketHandler(packetIo), _clientSessionRepository(clientSessionRepository),
          _clientConnectionSession(clientConnectionSession) {}

void ConnectAckPacketHandler::handle(RawPacket *rawPacket) {
    printf("handling connection ack packet\n");
    ConnectAckPacket *packet = static_cast<ConnectAckPacket *>(rawPacket);
    assertSpecificFlagsZero(packet);
    unsigned char retCode = packet->getReturnCode();
    ConnectPacket *connectPacket = _clientConnectionSession->getConnectPacket();

    switch (retCode) {
        case 0:
            printf("Connection Accepted by Server\n");
            if(_clientSessionRepository->load(connectPacket->getClientId()) == 0){
                printf("No Client Session yet, creating one\n");
                ClientSession* clientSession = new ClientSession(connectPacket->getClientId(),connectPacket->getUsername(),connectPacket->getPassword());
                _clientSessionRepository->save(clientSession);
            } else {
                printf("Client Session is present already\n");
            }
            break;
        case 1:
            throw InvalidPacketException("Connection Refused, unacceptable protocol version");
            break;
        case 2:
            throw InvalidPacketException("Connection Refused, identifier rejected");
            break;
        case 3:
            throw InvalidPacketException("Connection Refused, Server unavailable");
            break;
        case 4:
            throw InvalidPacketException("Connection Refused, bad user name or _password");
            break;
        case 5:
            throw InvalidPacketException("Connection Refused, not authorized");
            break;
        default:
            throw InvalidPacketException("Connection Refused, unknown error");
            break;
    }
}
