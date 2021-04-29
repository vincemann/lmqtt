//
// Created by vince on 07.04.21.
//


#include <stdio.h>

#include "ConnectPacketHandler.h"
#include "../ConnectionSession.h"
#include "exception/IllegalSessionStateException.h"
#include "exception/InvalidPacketException.h"
#include "../packets/RawPacket.h"
#include "../packets/ConnectAckPacket.h.h"
#include "../io/PacketIOManager.h"
#include "../Session.h"




void ConnectPacketHandler::connAck(int errorCode, const char* msg,unsigned char cleanSessionFlag, bool closeCon){
    printf("%s\n", msg);
    ConnectAckPacket *connectAckPacket = getConnectAckPacketFactory()->create(errorCode,cleanSessionFlag);
    packetIo->sendPacket(connectAckPacket);
    if (closeCon){
        closeConnection();
    }
}

void ConnectPacketHandler::closeConnectionWithoutAck(const char* errorMsg){
    printf("%s\n", msg);
    printf("Closing Connection without ack\n");
    closeConnection();
}

void ConnectPacketHandler::handle(RawPacket *rawPacket) {
    ConnectPacket* packet = dynamic_cast<ConnectPacket*>(rawPacket);
    printf("handling connect rawPacket:\n");
    if (_connectionSession->_packets_received->size() != 1){
        throw new IllegalSessionStateException("received more than one Connect Packet");
    }
    if (strcmp(packet->getProtocolName(), "MQTT") != 0){
        closeConnectionWithoutAck("invalid protocol name");
    }

    if (packet->getProtocolLevel() != 4){
        connAck(0x1, "invalid protocol level",packet->getCleanSession());
    }

    if (packet->getReservedBit() != 0){
        closeConnectionWithoutAck("reserved bit must not be set");
    }


    if (packet->getWillFlag()){
        if (packet->getWillQos() == 0x3){
            closeConnectionWithoutAck("Invalid Will QOS value 3");
        }
    } else{
        if (packet->getWillQos() != 0x0){
            closeConnectionWithoutAck("Invalid Will QOS value, must be 0 when willFlag is ß")
        }
        if(packet->getWillRetain() != 0){
            closeConnectionWithoutAck("Invalid Will Retain value, must be 0 when willFlag is ß")
        }
    }
    char* clientId = packet->getClientId();
    if (clientId == 0x0){
        closeConnectionWithoutAck("No Client id specified");
    }
    if (strlen(clientId) == 0){
        connAck(0x1, "Server Side ClientId generation unsupported",packet->getCleanSession());
    }
    if ( (strlen(clientId) > 23) || (strlen(clientId) < 1) ){
        closeConnectionWithoutAck("Invalid Client id size");
    }

    if (! isalnum(clientId) ){
        closeConnectionWithoutAck("Client id must be alphanumerical");
    }
    // init client session
    Session *session = new Session()
    strcpy(session->_clientId, packet->getClientId());
    _connectionSession->_session=session;
    connAck(0x0,"successful connect packet received",packet->getCleanSession(),false);

}

ConnectAckPacketFactory *ConnectPacketHandler::getConnectAckPacketFactory() const {
    return connectAckPacketFactory;
}


ConnectPacketHandler::ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory *connectAckPacketFactory)
        : PacketHandler(connectionSession, packetIo), _connectAckPacketFactory(connectAckPacketFactory) {

}



