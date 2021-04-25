//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKET_H
#define LMQTT__SERVER_CONNECTPACKET_H

#include "RawPacket.h"

class ConnectPacket : public RawPacket{
public:

    ConnectPacket(RawPacket *rawPacket, char *protocolName, unsigned char protocolLevel, unsigned char reservedBit,
                  unsigned char cleanSession, unsigned char willFlag, unsigned char willQos, unsigned char willRetain,
                  unsigned char passwordFlag, unsigned char usernameFlag, unsigned short keepAlive, char *clientId,
                  char *willTopic, char *willMsg, char *username, char *password);

    char *getProtocolName() const;

    unsigned char getProtocolLevel() const;

    unsigned char getReservedBit() const;

    unsigned char getCleanSession() const;

    unsigned char getWillFlag() const;

    unsigned char getWillQos() const;

    unsigned char getWillRetain() const;

    unsigned char getPasswordFlag() const;

    unsigned char getUsernameFlag() const;

    unsigned char getKeepAlive() const;

    char *getClientId() const;

    char *getWillTopic() const;

    char *getWillMsg() const;

    char *getUsername() const;

    char *getPassword() const;

    ~ConnectPacket();



private:
    char *protocolName;
    unsigned char protocolLevel;
    unsigned char reservedBit;
    unsigned char cleanSession;
    unsigned char willFlag;
    unsigned char willQos;
    unsigned char willRetain;
    unsigned char passwordFlag;
    unsigned char usernameFlag;
    unsigned short keepAlive;
    char *clientId;
    char *willTopic;
    char *willMsg;
    char *username;
    char *password;

};

#endif //LMQTT__SERVER_CONNECTPACKET_H
