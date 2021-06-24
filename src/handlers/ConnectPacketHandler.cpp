//
// Created by vince on 07.04.21.
//


#include <stdio.h>
#include <iostream>


#include "../con/ConnectionSession.h"
#include "exception/IllegalSessionStateException.h"
#include "exception/InvalidPacketException.h"
#include "../packets/ConnectAckPacket.h"
#include "../io/PacketIOManager.h"
#include "../session/ServerSession.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "ConnectPacketHandler.h"
#include <ServerSessionRepository.h>




void ConnectPacketHandler::connAck(int errorCode, unsigned char cleanSessionFlag){
    ConnectAckPacket *connectAckPacket = getConnectAckPacketFactory()->create(errorCode,cleanSessionFlag);
    _packetIo->sendPacket(connectAckPacket);
}

void ConnectPacketHandler::initServerSession(unsigned char cleanSession, char* clientId){
    if (cleanSession == 0)
    {
        ServerSession* session = _sessionRepository->load(clientId);
        if (session == nullptr)
        {
            std::cout << "did not find session file for client id" << clientId << "\n";
            std::cout << "creating it" << "\n";
            session = new ServerSession(strdup(clientId));
            _sessionRepository->save(session);
            std::cout << "new session: " << session << "\n";
        } else{
            std::cout << "have found session file for client id" << clientId << ": " << session <<"\n";
        }
    }
}


void ConnectPacketHandler::handle(RawPacket *rawPacket) {
    ConnectPacket* packet = static_cast<ConnectPacket*>(rawPacket);
    printf("handling connect rawPacket:\n");
    if (_connectionSession->_packets_received->size() != 1){
        throw IllegalSessionStateException("received more than one Connect Packet");
    }
    if (strcmp(packet->getProtocolName(), "MQTT") != 0){
        throw InvalidPacketException("invalid protocol name");
    }

    if (packet->getProtocolLevel() != 4){
        connAck(0x1,packet->getCleanSession());
        throw InvalidPacketException("invalid protocol level");
    }

    if (packet->getReservedBit() != 0){
        throw InvalidPacketException("reserved bit must not be set");
    }


    if (packet->getWillFlag()){
        if (packet->getWillQos() == 0x3){
            throw InvalidPacketException("Invalid Will QOS value 3");
        }
    } else{
        if (packet->getWillQos() != 0x0){
            throw InvalidPacketException("Invalid Will QOS value, must be 0 when willFlag is ß");
        }
        if(packet->getWillRetain() != 0){
            throw InvalidPacketException("Invalid Will Retain value, must be 0 when willFlag is ß");
        }
    }
    char* clientId = packet->getClientId();
    if (clientId == nullptr){
        throw InvalidPacketException("No Client id specified");
    }
    if (strlen(clientId) == 0){
        connAck(0x1,packet->getCleanSession());
        throw InvalidPacketException( "Server Side ClientId generation unsupported");
    }
    if ( (strlen(clientId) > 23) || (strlen(clientId) < 1) ){
        throw InvalidPacketException("Invalid Client id size");
    }

    if (! Utils::isAlNum(clientId) ){
        throw InvalidPacketException("Client id must be alphanumerical");
    }

    
    printf("%s\n","valid connect packet received, initializing session");
    unsigned char cleanSession = packet->getCleanSession();


    // init server session
    initServerSession(cleanSession, clientId);
    connAck(0x0, cleanSession);
}

ConnectAckPacketFactory *ConnectPacketHandler::getConnectAckPacketFactory() const {
    return _connectAckPacketFactory;
}

ConnectPacketHandler::ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,
                                           ConnectAckPacketFactory *connectAckPacketFactory,
                                           ServerSessionRepository *sessionRepository) : PacketHandler(
        connectionSession, packetIo), _connectAckPacketFactory(connectAckPacketFactory), _sessionRepository(
        sessionRepository) {}





