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
    printf("handling connect ack packet\n");
    ConnectAckPacket* packet = static_cast<ConnectAckPacket*>(rawPacket);
    unsigned char retCode = packet->getReturnCode();
    switch (retCode)
    {
    case 0:
        /* code */
        printf("Connection Accepted by Server\n");
        ConnectPacket* connectPacket = _clientConnectionSession->_connectPacket;
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

    // todo implement session state
}
