//
// Created by vince on 23.04.21.
//

#include "ConnectPacketFactory.h"
#include "../ConnectPacket.h"
#include "../../packets/RawPacket.h"
#include "../PacketType.h"
#include "../../handlers/ConnectPacketHandler.h"
#include "../../util/Utils.h"
#include "../Payload.h"




ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, char *clientId, char *username,
                                            char *password) {
    return create(cleanSession,0,0,0,clientId,0,0,username,password);
}

ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                                        unsigned char willRetain,
                                        char *clientId, char *willTopic, char *willMsg, char *username,
                                        char *password) {

    unsigned char specificFlags = 0;

    unsigned char passwordFlag = 0;
    if (password != 0){
        passwordFlag = 1;
    }

    unsigned char usernameFlag = 0;
    if (username != 0){
        usernameFlag = 1;
    }

    char* protocolName = "MQTT";
    Payload* protocolNamePayload = PacketFactory::createUtf8Payload(protocolName);
    unsigned char protocolLevel = 4;
    Payload* protocolLevelPayload = new Payload(protocolLevel);

    unsigned char reservedBit = 0;
    unsigned char connectFlags = reservedBit |
            (cleanSession << 1)  |
            (willFlag << 2 ) |
            (willQos << 4 ) |
            (willRetain << 5 ) |
            (passwordFlag << 6 ) |
            (usernameFlag << 7 );

    // 3 minutes
    unsigned short keepAlive = 180;
    Payload* keepAlivePayload = new Payload(keepAlive,sizeof(unsigned short));

    Payload* connectFlagsPayload = new Payload(connectFlags);
    Payload* clientIdPayload = PacketFactory::createUtf8Payload(clientId);

    Payload* willTopicPayload = 0;
    Payload* willMsgPayload = 0;
    if (willFlag){
        willTopicPayload = PacketFactory::createUtf8Payload(willTopic);
        willMsgPayload = PacketFactory::createUtf8Payload(willMsg);
    }

    Payload* usernamePayload = 0;
    if (usernameFlag){
        usernamePayload = PacketFactory::createUtf8Payload(username);
    }

    Payload* passwordPayload = 0;
    if (passwordFlag){
        passwordPayload = PacketFactory::createUtf8Payload(password);
    }

    int payloadLen;
    const Payload* toMerge[] = {protocolNamePayload, protocolLevelPayload,
                             connectFlagsPayload, clientIdPayload, willTopicPayload,
                             willMsgPayload, usernamePayload,keepAlivePayload, passwordPayload};
    unsigned char* payload = PacketFactory::mergePayloads(&payloadLen, toMerge, 9);

//    printf("payload:%.*s\n", *payloadLen, (char*) payload);
    Utils::printChars(payload, payloadLen);

    RawPacket *rawPacket = new RawPacket(specificFlags,payload,payloadLen,CONNECT);
    return new ConnectPacket(rawPacket, protocolName, protocolLevel, reservedBit, cleanSession, willFlag, willQos, willRetain,
                             passwordFlag, usernameFlag,keepAlive, clientId, willTopic, willMsg, username, password);
}


