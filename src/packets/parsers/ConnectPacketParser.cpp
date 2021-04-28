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
    unsigned char *pData = pRawPacket->getData();
    // extract variable header
    char *protocolName = extractUtf8Payload(&pData, false);
    printf("protocolName:%s\n", protocolName);

    unsigned char protocolLevel = pData[6];
    printf("protocolLevel:%d\n", protocolLevel);


    unsigned char connectFlags = pData[7];
    printf("Binary connectFlags:");
    Utils::printBits(connectFlags);

    unsigned char reservedBit = (connectFlags >> 0) & 1;

    unsigned char cleanSessionFlag = (connectFlags >> 1) & 1;
    unsigned char willFlag = (connectFlags >> 2) & 1;
    unsigned char willQos1 = (connectFlags >> 3) & 1;
    unsigned char willQos2 = (connectFlags >> 4) & 1;
    unsigned char willQos = (willQos1 << 1) | willQos2;
    unsigned  char willRetainFlag = (connectFlags >> 5) & 1;
    unsigned char passwordFlag = (connectFlags >> 6) & 1;
    unsigned char usernameFlag = (connectFlags >> 7) & 1;

    unsigned short keepAlive = (pData[8] << 8) | pData[9];

    pData += 10;
    // now comes payload
    // in this order Client Identifier, Will Topic, Will Message, User Name, Password
    // depends on variable header bits
    char *clientId = extractUtf8Payload(&pData);
    printf("clientId:%s\n", clientId);


    char *willTopic = 0;
    char *willMsg = 0;
    if (willFlag) {
        willTopic = extractUtf8Payload(&pData);
        willMsg = extractUtf8Payload(&pData);
        printf("willTopic:%s\n",willTopic);
        printf("willMsg:%s\n",willMsg);
    }

    char *username = 0;
    if (usernameFlag) {
        username = extractUtf8Payload(&pData);
        printf("username:%s\n",username);

    }


    char *password = 0;
    if (passwordFlag) {
        password = extractUtf8Payload(&pData);
        printf("password:%s\n",password);
    }


    return new ConnectPacket(pRawPacket,protocolName, protocolLevel, reservedBit,
                             cleanSessionFlag, willFlag, willQos,
                             willRetainFlag, passwordFlag, usernameFlag,keepAlive,
                             clientId, willTopic, willMsg, username, password);
}
