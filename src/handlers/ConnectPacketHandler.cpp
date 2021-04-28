//
// Created by vince on 07.04.21.
//


#include <stdio.h>

#include "ConnectPacketHandler.h"
#include "../Session.h"
#include "exception/IllegalSessionStateException.h"
#include "exception/InvalidPacketException.h"
#include "../packets/RawPacket.h"
#include "../io/PacketIOManager.h"

ConnectPacketHandler::ConnectPacketHandler(Session *session, PacketIOManager *packetIo) : PacketHandler(session, NULL) {}


static void connAck(int errorCode, const char* msg, PacketIOManager *packetIo, bool closeConnection=true){
    printf("%s\n", msg);
    //    packetIo->sendPacket()
    if (closeConnection){
        throw new InvalidPacketException(errorMsg);
    }
}

static void closeConnectionWithoutAck(const char* errorMsg){
    throw new InvalidPacketException(errorMsg);
}

void ConnectPacketHandler::handle(RawPacket *rawPacket) {
    ConnectPacket* packet = dynamic_cast<ConnectPacket*>(rawPacket);
    printf("handling connect rawPacket:\n");
    if (_session->_packets_received->size() != 1){
        throw new IllegalSessionStateException("received more than one Connect Packet");
    }
    if (strcmp(packet->protocolName, "MQTT") != 0){
        closeConnectionWithoutAck("invalid protocol name");
    }

    if (packet->protocolLevel != 4){
        connAck(0x1, "invalid protocol level",packetIo);
    }

    if (packet->reservedBit != 0){
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
        connAck(0x1, "Server Side ClientId generation unsupported",packetIo);
    }
    if ( (strlen(clientId) > 23) || (strlen(clientId) < 1) ){
        closeConnectionWithoutAck("Invalid Client id size");
    }

    if (! isalnum(clientId) ){
        closeConnectionWithoutAck("Client id must be alphanumerical");
    }

    strcpy(_session->_clientId, packet->getClientId());
    connAck(0x0,"successful connect packet received",packetIo,false);

}

