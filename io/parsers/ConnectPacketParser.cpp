//
// Created by vince on 06.04.21.
//

#include "ConnectPacketParser.h"
#include "../../packets/ConnectPacket.h"
#include "../exception/PacketParsingException.h"
#include "../../util/Utils.h"

#include <stdio.h>
#include <string.h>

static char *extractUtf8Payload(char *p, bool incrementPointer = true) {
    // todo check for wrong encoding chars -> close connection
    unsigned short len = getUf8PayloadLen(p);
    char payload[len + 1];
    Utils::extractSubArray(p, payload, len);
    // check for null bytes
    for (int i = 0; i < len - 1; ++i) {
        char c = payload[i];
        if (c == '\0') {
            throw new PacketParsingException("payload must not contain nullbytes");
        }
    }
    // add trailing null byte
    payload[len] = '\0';
    if (incrementPointer) {
        p += len;
    }
    return strdup(payload);
}

RawPacket *ConnectPacketParser::parse(RawPacket *pRawPacket) {
    if (pRawPacket->getSpecificFlags() != 0) {
        // all specific flags must be 0
        throw new PacketParsingException("invalid specific flags");
    }
    unsigned char *pData = pRawPacket->getData()
    // extract variable header
    unsigned  char *protocolName = extractUtf8Payload(pData, false);
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
    unsigned char *clientId = extractUtf8Payload(pData);
    printf("clientId:%s\n", clientId);

    char *willTopic = 0;
    if (willFlag) {
        willTopic = extractUtf8Payload(pData);
        printf("willTopic:%s\n",willTopic)

    }



    unsigned char *willTopic = 0;
    unsigned char *willMsg = 0;
    if (willFlag) {
        willTopic = extractUtf8Payload(pData);
        willMsg = extractUtf8Payload(pData);
        printf("willTopic:%s\n",willTopic)
        printf("willMsg:%s\n",willMsg)
    }

    unsigned char *username = 0;
    if (usernameFlag) {
        username = extractUtf8Payload(pData);
        printf("username:%s\n",username)

    }


    unsigned char *password = 0;
    if (passwordFlag) {
        password = extractUtf8Payload(pData);
        printf("password:%s\n",password)
    }


    return new ConnectPacket(pRawPacket->getLength(),pRawPacket->getType(),protocolName, protocolLevel, reservedBit,
                             cleanSessionFlag, willFlag, willQos,
                             willRetainFlag, passwordFlag, usernameFlag,
                             clientId, willTopic, willMsg, username, password
    );
}
