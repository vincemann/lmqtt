//
// Created by vince on 07.04.21.
//


#include <stdio.h>
#include <iostream>


#include "../con/ConnectionSession.h"
#include "exception/IllegalSessionStateException.h"
#include "exception/InvalidPacketException.h"
#include "../packets/RawPacket.h"
#include "../packets/ConnectAckPacket.h"
#include "../io/PacketIOManager.h"
#include "../session/Session.h"
#include "../util/Utils.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "ConnectPacketHandler.h"
#include "../files/FileDataManager.h"




void ConnectPacketHandler::connAck(int errorCode, unsigned char cleanSessionFlag){
    ConnectAckPacket *connectAckPacket = getConnectAckPacketFactory()->create(errorCode,cleanSessionFlag);
    packetIo->sendPacket(connectAckPacket);
}

Session* ConnectPacketHandler::findSession(char* clientId){
    // char* sessionFileData = _fileDataManager->find("~/.lmqtt", clientId);
    // char* sessionFileData = _fileDataManager->find("test", clientId);
    char* sessionFileData = 0;
    if (sessionFileData == 0)
    {
        std::cout << "did not find session file for client id" << clientId << "\n";
        return 0;
    }else{
        std::cout << "did find session file for client id" << clientId << ": " << *sessionFileData <<"\n";
        return 0;
    }
}

Session* ConnectPacketHandler::createSession(unsigned char cleanSession, char* clientId){
    if (cleanSession == 0)
    {
         // check if there is already a session and use, otherwise gen one
         findSession(clientId);
    }else{
        // remove old session if there is any and gen new
    }
}

void ConnectPacketHandler::handle(RawPacket *rawPacket) {
    ConnectPacket* packet = static_cast<ConnectPacket*>(rawPacket);
    printf("handling connect rawPacket:\n");
    if (_connectionSession->_packets_received->size() != 1){
        throw new IllegalSessionStateException("received more than one Connect Packet");
    }
    if (strcmp(packet->getProtocolName(), "MQTT") != 0){
        throw new InvalidPacketException("invalid protocol name");
    }

    if (packet->getProtocolLevel() != 4){
        connAck(0x1,packet->getCleanSession());
        throw new InvalidPacketException("invalid protocol level");
    }

    if (packet->getReservedBit() != 0){
        throw new InvalidPacketException("reserved bit must not be set");
    }


    if (packet->getWillFlag()){
        if (packet->getWillQos() == 0x3){
            throw new InvalidPacketException("Invalid Will QOS value 3");
        }
    } else{
        if (packet->getWillQos() != 0x0){
            throw new InvalidPacketException("Invalid Will QOS value, must be 0 when willFlag is ß");
        }
        if(packet->getWillRetain() != 0){
            throw new InvalidPacketException("Invalid Will Retain value, must be 0 when willFlag is ß");
        }
    }
    char* clientId = packet->getClientId();
    if (clientId == 0x0){
        throw new InvalidPacketException("No Client id specified");
    }
    if (strlen(clientId) == 0){
        connAck(0x1,packet->getCleanSession());
        throw new InvalidPacketException( "Server Side ClientId generation unsupported");
    }
    if ( (strlen(clientId) > 23) || (strlen(clientId) < 1) ){
        throw new InvalidPacketException("Invalid Client id size");
    }

    if (! Utils::isAlNum(clientId) ){
        throw new InvalidPacketException("Client id must be alphanumerical");
    }

    
    printf("%s\n","valid connect packet received, initializing session");
    unsigned char cleanSession = packet->getCleanSession();
    
    


    // init client session
    Session *session = new Session();
    session->_clientId = strdup(packet->getClientId());
    _connectionSession->_session=session;

    connAck(0x0,packet->getCleanSession());
}

ConnectAckPacketFactory *ConnectPacketHandler::getConnectAckPacketFactory() const {
    return _connectAckPacketFactory;
}


ConnectPacketHandler::ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory *connectAckPacketFactory, FileDataManager* fileDataManager)
        : PacketHandler(connectionSession, packetIo),
         _connectAckPacketFactory(connectAckPacketFactory),
          _fileDataManager(fileDataManager) 
          {

}



