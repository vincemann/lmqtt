//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"
#include "ConnectPacket.h"


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

unsigned char *ConnectPacket::getClientId() const {
    return clientId;
}

unsigned char *ConnectPacket::getWillTopic() const {
    return willTopic;
}

unsigned char *ConnectPacket::getWillMsg() const {
    return willMsg;
}

unsigned char *ConnectPacket::getUsername() const {
    return username;
}

unsigned char *ConnectPacket::getPassword() const {
    return password;
}

ConnectPacket::~ConnectPacket(){
    delete clientId;
    delete willTopic;
    delete willMsg;
    delete username;
    delete password;
    delete protocolName;
}

//ConnectPacket::ConnectPacket(RawPacket *rawPacket, unsigned char protocolLevel, unsigned char *protocolName,
//                             unsigned char reservedBit, unsigned char cleanSession, unsigned char willFlag,
//                             unsigned char willQos, unsigned char willRetain, unsigned char passwordFlag,
//                             unsigned char usernameFlag, unsigned char *clientId, unsigned char *willTopic,
//                             unsigned char *willMsg, unsigned char *username, unsigned char *password) : RawPacket(
//        rawPacket), protocolLevel(protocolLevel), protocolName(protocolName), reservedBit(reservedBit), cleanSession(
//        cleanSession), willFlag(willFlag), willQos(willQos), willRetain(willRetain), passwordFlag(passwordFlag),
//                                                                                                         usernameFlag(
//                                                                                                                 usernameFlag),
//                                                                                                         clientId(
//                                                                                                                 clientId),
//                                                                                                         willTopic(
//                                                                                                                 willTopic),
//                                                                                                         willMsg(willMsg),
//                                                                                                         username(
//                                                                                                                 username),
//                                                                                                         password(
//                                                                                                                 password) {}
//
//ConnectPacket::ConnectPacket(unsigned char protocolLevel, unsigned char *protocolName, unsigned char reservedBit,
//                             unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
//                             unsigned char willRetain, unsigned char passwordFlag, unsigned char usernameFlag,
//                             unsigned char *clientId, unsigned char *willTopic, unsigned char *willMsg,
//                             unsigned char *username, unsigned char *password) : protocolLevel(protocolLevel),
//                                                                                 protocolName(protocolName),
//                                                                                 reservedBit(reservedBit),
//                                                                                 cleanSession(cleanSession),
//                                                                                 willFlag(willFlag), willQos(willQos),
//                                                                                 willRetain(willRetain),
//                                                                                 passwordFlag(passwordFlag),
//                                                                                 usernameFlag(usernameFlag),
//                                                                                 clientId(clientId),
//                                                                                 willTopic(willTopic), willMsg(willMsg),
//                                                                                 username(username),
//                                                                                 password(password) {}

unsigned char ConnectPacket::getProtocolLevel() const {
    return protocolLevel;
}

unsigned char *ConnectPacket::getProtocolName() const {
    return protocolName;
}

unsigned char ConnectPacket::getReservedBit() const {
    return reservedBit;
}

ConnectPacket::ConnectPacket(RawPacket *rawPacket, unsigned char *protocolName, unsigned char protocolLevel,
                             unsigned char reservedBit, unsigned char cleanSession, unsigned char willFlag,
                             unsigned char willQos, unsigned char willRetain, unsigned char passwordFlag,
                             unsigned char usernameFlag, unsigned char *clientId, unsigned char *willTopic,
                             unsigned char *willMsg, unsigned char *username, unsigned char *password) : RawPacket(
        rawPacket), protocolName(protocolName), protocolLevel(protocolLevel), reservedBit(reservedBit), cleanSession(
        cleanSession), willFlag(willFlag), willQos(willQos), willRetain(willRetain), passwordFlag(passwordFlag),
                                                                                                         usernameFlag(
                                                                                                                 usernameFlag),
                                                                                                         clientId(
                                                                                                                 clientId),
                                                                                                         willTopic(
                                                                                                                 willTopic),
                                                                                                         willMsg(willMsg),
                                                                                                         username(
                                                                                                                 username),
                                                                                                         password(
                                                                                                                 password) {}



