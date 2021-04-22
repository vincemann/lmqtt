//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"
#include "ConnectPacket.h"


ConnectPacket::ConnectPacket(RawPacket *rawPacket, unsigned char cleanSession,
                             unsigned char willFlag, unsigned char willQos, unsigned char willRetain,
                             unsigned char passwordFlag, unsigned char usernameFlag, unsigned char *clientId,
                             unsigned char *willTopic, unsigned char *willMsg, unsigned char *username,
                             unsigned char *password) : RawPacket(rawPacket), cleanSession(cleanSession),
                                                        willFlag(willFlag), willQos(willQos), willRetain(willRetain),
                                                        passwordFlag(passwordFlag), usernameFlag(usernameFlag),
                                                        clientId(clientId), willTopic(willTopic), willMsg(willMsg),
                                                        username(username), password(password) {}

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

ConnectPacket::~ConnectPacket() : ~RawPacket() {
    delete clientId;
    delete willTopic;
    delete willMsg;
    delete username;
    delete password;
}

ConnectPacket::ConnectPacket(unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                             unsigned char willRetain, unsigned char passwordFlag, unsigned char usernameFlag,
                             unsigned char *clientId, unsigned char *willTopic, unsigned char *willMsg,
                             unsigned char *username, unsigned char *password) : cleanSession(cleanSession),
                                                                                 willFlag(willFlag), willQos(willQos),
                                                                                 willRetain(willRetain),
                                                                                 passwordFlag(passwordFlag),
                                                                                 usernameFlag(usernameFlag),
                                                                                 clientId(clientId),
                                                                                 willTopic(willTopic), willMsg(willMsg),
                                                                                 username(username),
                                                                                 password(password) {
    // todo generate raw packet and set super fields
}



