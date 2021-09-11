//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"
#include "ConnectPacket.h"






ConnectPacket::ConnectPacket(RawPacket *rawPacket, char *protocolName, unsigned char protocolLevel,
                             unsigned char reservedBit, unsigned char cleanSession, unsigned char willFlag,
                             unsigned char willQos, unsigned char willRetain, unsigned char passwordFlag,
                             unsigned char usernameFlag, unsigned short keepAlive, char *clientId, char *willTopic,
                             char *willMsg, char *username, char *password)
        : RawPacket(rawPacket),
          protocolName(protocolName),
          protocolLevel(protocolLevel),
          reservedBit(reservedBit),
          cleanSession(cleanSession),
          willFlag(willFlag), willQos(willQos),
          willRetain(willRetain),
          passwordFlag(passwordFlag),
          usernameFlag(usernameFlag),
          keepAlive(keepAlive), clientId(clientId),
          willTopic(willTopic), willMsg(willMsg),
          username(username), password(password) {}

char *ConnectPacket::getProtocolName() const {
    return protocolName;
}

unsigned char ConnectPacket::getProtocolLevel() const {
    return protocolLevel;
}

unsigned char ConnectPacket::getReservedBit() const {
    return reservedBit;
}

unsigned char ConnectPacket::getCleanSession() const {
    return cleanSession;
}

unsigned char ConnectPacket::getWillFlag() const {
    return willFlag;
}

unsigned char ConnectPacket::getWillQos() const {
    return willQos;
}

unsigned char ConnectPacket::getWillRetain() const {
    return willRetain;
}

unsigned char ConnectPacket::getPasswordFlag() const {
    return passwordFlag;
}

unsigned char ConnectPacket::getUsernameFlag() const {
    return usernameFlag;
}

unsigned char ConnectPacket::getKeepAlive() const {
    return keepAlive;
}

char *ConnectPacket::getClientId() const {
    return clientId;
}

char *ConnectPacket::getWillTopic() const {
    return willTopic;
}

char *ConnectPacket::getWillMsg() const {
    return willMsg;
}

char *ConnectPacket::getUsername() const {
    return username;
}

char *ConnectPacket::getPassword() const {
    return password;
}





