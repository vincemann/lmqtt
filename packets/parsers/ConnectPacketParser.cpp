//
// Created by vince on 06.04.21.
//

#include "ConnectPacketParser.h"
#include "../ConnectPacket.h"
#include "exception/PacketParsingException.h"
#include "../../util/Utils.h"

#include <stdio.h>
#include <string.h>


RawPacket *ConnectPacketParser::parse(RawPacket *pRawPacket) {
    if (pRawPacket->getSpecificFlags() != 0) {
        // all specific flags must be 0
        throw new PacketParsingException("invalid specific flags");
    }
    unsigned char *pData = pRawPacket->getData()
    // extract variable header
    unsigned  char *protocolName = PacketParser::extractUtf8Payload(pData, false);
    printf("protocolName:%s\n", protocolName)

    // todo all those checks put into ConnectPacketHandler
    // this class only builds the ConnectPacket and does not verify
//    if (strcmp(protocolName,"MQTT") != 0){
//        throw new PacketParsingException("invalid protocol name");
//    }
    unsigned char protocolLevel = pData[7];
    printf("protocolLevel:%d\n", protocolLevel)

//    if (protocolLevel != 4){
//        // todo respond with connack return code 1 instead
//        throw new PacketParsingException("invalid protocol level");
//    }
    unsigned char connectFlags = pData[8];
    printf("Binary connectFlags:")
    Utils::print_bits(connectFlags);

    unsigned char reservedBit = (connectFlags >> 0) & 1;
//    if (reservedBit != 0){
//        throw new PacketParsingException("reserved bit must not be set");
//    }
    unsigned char cleanSessionFlag = (connectFlags >> 1) & 1;
    unsigned char willFlag = (connectFlags >> 2) & 1;
    unsigned char willQos1 = (connectFlags >> 3) & 1;
    unsigned char willQos2 = (connectFlags >> 4) & 1;
    unsigned char willQos = (willQos1 << 1) | willQos2;
    unsigned  char willRetainFlag = (connectFlags >> 5) & 1;
    unsigned char passwordFlag = (connectFlags >> 6) & 1;
    unsigned char usernameFlag = (connectFlags >> 7) & 1;

    unsigned short = keepAlive = (pData[9] << 8) | pData[10];

    pData += 10;
    // now comes payload
    // in this order Client Identifier, Will Topic, Will Message, User Name, Password
    // depends on variable header bits
    unsigned char *clientId = PacketParser::extractUtf8Payload(pData);
    printf("clientId:%s\n", clientId);

    char *willTopic = 0;
    if (willFlag) {
        willTopic = PacketParser::extractUtf8Payload(pData);
        printf("willTopic:%s\n",willTopic)

    }



    unsigned char *willTopic = 0;
    unsigned char *willMsg = 0;
    if (willFlag) {
        willTopic = PacketParser::extractUtf8Payload(pData);
        willMsg = PacketParser::extractUtf8Payload(pData);
        printf("willTopic:%s\n",willTopic)
        printf("willMsg:%s\n",willMsg)
    }

    unsigned char *username = 0;
    if (usernameFlag) {
        username = PacketParser::extractUtf8Payload(pData);
        printf("username:%s\n",username)

    }


    unsigned char *password = 0;
    if (passwordFlag) {
        password = PacketParser::extractUtf8Payload(pData);
        printf("password:%s\n",password)
    }


    return new ConnectPacket(pRawPacket, protocolLevel,protocolName, reservedBit,
                             cleanSessionFlag, willFlag, willQos,
                             willRetainFlag, passwordFlag, usernameFlag,
                             clientId, willTopic, willMsg, username,password);
}
