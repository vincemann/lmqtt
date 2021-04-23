//
// Created by vince on 23.04.21.
//

#include "ConnectPacketFactory.h"
#include "../../packets/ConnectPacket.h"
#include "../../packets/RawPacket.h.h"
#include "../../packets/PacketType.h"

// give me ConnectPacket with raw packet null and i will gen raw packet ready to send
RawPacket *ConnectPacketFactory::create(RawPacket *raw_packet) {
    ConnectPacket* connectPacket = dynamic_cast<ConnectPacket*>(raw_packet);
    // IO Manager puts this into packet for me
    connectPacket.setType(CONNECT);
    connectPacket.setSpecificFlags(0);

    unsigned char* protocolName = PacketFactory::createUtf8Payload("MQTT");
    unsigned char protocolLevel = 4;

    unsigned char connectFlags = connectPacket->getReservedBit() |
            (connectPacket->getCleanSession() << 1)  |
            (connectPacket->getWillFlag() << 2 ) |
            (connectPacket->getWillQos() << 4 ) |
            (connectPacket->getWillRetain() << 5 ) |
            (connectPacket->getPasswordFlag() << 6 ) |
            (connectPacket->getUsernameFlag() << 7 ) |;

    unsigned char* clientId = PacketFactory::createUtf8Payload(connectPacket->getClientId());

    unsigned char* willTopic = 0;
    unsigned char* willMsg = 0;
    if (connectPacket->getWillFlag()){
        willTopic = PacketFactory::createUtf8Payload(connectPacket->getWillTopic());
        willMsg = PacketFactory::createUtf8Payload(connectPacket->getWillMsg());
    }

    unsigned char* username = 0;
    if (connectPacket->getUsernameFlag()){
        username = PacketFactory::createUtf8Payload(connectPacket->getUsername());
    }

    unsigned char* password = 0;
    if (connectPacket->getPasswordFlag()){
        password = PacketFactory::createUtf8Payload(connectPacket->getPassword());
    }

    unsigned int payloadLen =
            strlen(protocolName) +
            1 +
            1 +
            strlen(clientId) +
            strlen(willTopic) +
            strlen(willMsg) +
            strlen(username) +
            strlen(password);
    unsigned char payload[payloadLen];
    snprintf(payload,payloadLen,"%s%c%c%s%s%s%s%s",
             protocolName,protocolLevel,clientId,
             willTopic,willMsg,username,password);

    connectPacket->setData(payload);
    return connectPacket;
}
