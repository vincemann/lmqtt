//
// Created by vince on 23.04.21.
//

#include "ConnectPacketFactory.h"
#include "../../packets/ConnectPacket.h"
#include "../../packets/RawPacket.h.h"
#include "../../packets/PacketType.h"
#include "../../handlers/ConnectPacketHandler.h"
#include "../../util/Utils.h"




ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, unsigned char *clientId, unsigned char *username,
                                            unsigned char *password) {
    return create(cleanSession,0,0,0,clientId,0,0,username,password);
}

// give me ConnectPacket with raw packet null and i will gen raw packet ready to send
ConnectPacket *ConnectPacketFactory::create(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                                        unsigned char willRetain,
                                        unsigned char *clientId, unsigned char *willTopic, unsigned char *willMsg, unsigned char *username,
                                        unsigned char *password) {

    unsigned char specificFlags = 0;

    unsigned char passwordFlag = 0;
    if (password != 0){
        passwordFlag = 1;
    }

    unsigned char usernameFlag = 0;
    if (username != 0){
        usernameFlag = 1;
    }


    unsigned char* protocolName = PacketFactory::createUtf8Payload("MQTT");
    unsigned char protocolLevel = 4;

    unsigned char connectFlags = connectPacket->getReservedBit() |
            (cleanSession << 1)  |
            (willFlag << 2 ) |
            (willQos << 4 ) |
            (willRetain << 5 ) |
            (passwordFlag << 6 ) |
            (usernameFlag << 7 ) |;

    unsigned char* clientId = PacketFactory::createUtf8Payload(connectPacket->getClientId());

    unsigned char* willTopic = 0;
    unsigned char* willMsg = 0;
    if (willFlag){
        willTopic = PacketFactory::createUtf8Payload(connectPacket->getWillTopic());
        willMsg = PacketFactory::createUtf8Payload(connectPacket->getWillMsg());
    }

    unsigned char* username = 0;
    if (usernameFlag){
        username = PacketFactory::createUtf8Payload(connectPacket->getUsername());
    }

    unsigned char* password = 0;
    if (passwordFlag){
        password = PacketFactory::createUtf8Payload(connectPacket->getPassword());
    }

    unsigned int payloadLen =
            strlen(protocolName)+
            1 +
            1 +
            strlen(clientId) +
            strlen(willTopic) +
            strlen(willMsg) +
            strlen(username) +
            strlen(password);
    unsigned char payload[payloadLen];

    PacketFactory::memcpyStrings(payload,
            (char*[]){protocolName,&protocolLevel,
                      &connectFlags,clientId,willTopic,
                      willMsg,username,password,0xf});

    printf("payload:%." << payloadLen << "s\n",payload)

    RawPacket rawPacket = new RawPacket(specificFlags,payload,payloadLen,CONNECT);
    return new ConnectPacket(rawPacket,protocolName,protocolLevel,0,cleanSession,willFlag,willQos,willRetain,passwordFlag,usernameFlag,clientId,willTopic,willMsg,username,password);
}


