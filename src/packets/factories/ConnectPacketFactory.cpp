//
// Created by vince on 23.04.21.
//

#include "ConnectPacketFactory.h"
#include "../ConnectPacket.h"
#include "../../packets/RawPacket.h"
#include "../PacketType.h"
#include "../../handlers/ConnectPacketHandler.h"
#include "../../util/Utils.h"




ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, char *clientId, char *username,
                                            char *password) {
    return create(cleanSession,0,0,0,clientId,0,0,username,password);
}

ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                                        unsigned char willRetain,
                                        char *clientId, char *willTopic, char *willMsg, char *username,
                                        char *password) {

    // 3 minutes
    unsigned short keepAlive = 180;
    unsigned char specificFlags = 0;

    unsigned char passwordFlag = 0;
    if (password != 0){
        passwordFlag = 1;
    }

    unsigned char usernameFlag = 0;
    if (username != 0){
        usernameFlag = 1;
    }


    char* protocolName = PacketFactory::createUtf8Payload("MQTT");
    unsigned char protocolLevel = 4;

    unsigned char reservedBit = 0;
    unsigned char connectFlags = reservedBit |
            (cleanSession << 1)  |
            (willFlag << 2 ) |
            (willQos << 4 ) |
            (willRetain << 5 ) |
            (passwordFlag << 6 ) |
            (usernameFlag << 7 );

    char* clientIdPayload = PacketFactory::createUtf8Payload(clientId);

    char* willTopicPayload = 0;
    char* willMsgPayload = 0;
    if (willFlag){
        willTopicPayload = PacketFactory::createUtf8Payload(willTopic);
        willMsgPayload = PacketFactory::createUtf8Payload(willMsg);
    }

    char* usernamePayload = 0;
    if (usernameFlag){
        usernamePayload = PacketFactory::createUtf8Payload(username);
    }

    char* passwordPayload = 0;
    if (passwordFlag){
        passwordPayload = PacketFactory::createUtf8Payload(password);
    }

    unsigned int payloadLen =
            strlen(protocolName)+
            1 +
            1 +
            strlen(clientIdPayload) +
            strlen(willTopicPayload) +
            strlen(willMsgPayload) +
            strlen(usernamePayload) +
            strlen(passwordPayload);
    unsigned char payload[payloadLen];

    const void* toMerge[] = {protocolName, &protocolLevel,
                             &connectFlags, clientId, willTopic,
                             willMsg, username, password};
    PacketFactory::memcpyMergeStrings(payload, toMerge, 8);

    printf("payload:%.*s", payloadLen, (char*) payload);

    RawPacket *rawPacket = new RawPacket(specificFlags,payload,payloadLen,CONNECT);
    return new ConnectPacket(rawPacket, protocolName, protocolLevel, reservedBit, cleanSession, willFlag, willQos, willRetain,
                             passwordFlag, usernameFlag,keepAlive, clientId, willTopic, willMsg, username, password);
}


