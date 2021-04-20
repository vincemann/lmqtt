//
// Created by vince on 06.04.21.
//

#include "ConnectPacketParser.h"
#include "../../packets/ConnectPacket.h"
#include "../exception/PacketParsingException.h"
#include "../../util/Utils.h"

#include <stdio.h>
#include <string.h>

RawPacket* ConnectPacketParser::parse(RawPacket* pRawPacket) {
    if(pRawPacket->getSpecificFlags() != 0){
        // all specific flags must be 0
        throw new PacketParsingException("invalid specific flags");
    }

    // extract variable header
    unsigned short len = getUf8PayloadLen(pRawPacket->getData());
    if (len != 4){
        throw new PacketParsingException("invalid protocol name length");
    }
    char protocolName[len];
    Utils::extractSubArray(pRawPacket->getData(), protocolName, len);
    printf("Connect packet protocol name: %s\n",protocolName);

    // todo all those checks put into ConnectPacketHandler
    // this class only builds the ConnectPacket and does not verify


//    if (strcmp(protocolName,"MQTT") != 0){
//        throw new PacketParsingException("invalid protocol name");
//    }
    char protocolLevel = pRawPacket->getData()[7];
//    if (protocolLevel != 4){
//        // todo respond with connack return code 1 instead
//        throw new PacketParsingException("invalid protocol level");
//    }
    char connectFlags = pRawPacket->getData()[8];
    char reservedBit = (connectFlags >> 0) & 1;
//    if (reservedBit != 0){
//        throw new PacketParsingException("reserved bit must not be set");
//    }
    char cleanSession = (connectFlags >> 1) & 1;
    char willFlag = (connectFlags >> 2) & 1;
    char willQos1 = (connectFlags >> 3) & 1;
    char willQos2 = (connectFlags >> 4) & 1;
    char willQos = (willQos1 << 1) | willQos2;
    char willRetain = (connectFlags >> 5) & 1;
    char passwordFlag = (connectFlags >> 6) & 1;
    char usernameFlag = (connectFlags >> 7) & 1;

    unsigned short = keepAlive = (pRawPacket->getData()[9] << 8) | pRawPacket->getData()[10];

    // now comes payload
    // in this order Client Identifier, Will Topic, Will Message, User Name, Password
    // depends on variable header bits


    return new ConnectPacket(pRawPacket->getLength(), pRawPacket->getData());
}
