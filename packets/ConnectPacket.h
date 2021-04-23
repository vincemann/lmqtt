//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKET_H
#define LMQTT__SERVER_CONNECTPACKET_H

#include "RawPacket.h"
#include "RawPacket.h"

class ConnectPacket : RawPacket{
public:
    ConnectPacket(RawPacket *rawPacket, unsigned char protocolLevel, unsigned char *protocolName,
                  unsigned char reservedBit, unsigned char cleanSession, unsigned char willFlag, unsigned char willQos,
                  unsigned char willRetain, unsigned char passwordFlag, unsigned char usernameFlag,
                  unsigned char *clientId, unsigned char *willTopic, unsigned char *willMsg, unsigned char *username,
                  unsigned char *password);

    ConnectPacket(unsigned char protocolLevel, unsigned char *protocolName, unsigned char reservedBit,
                  unsigned char cleanSession, unsigned char willFlag, unsigned char willQos, unsigned char willRetain,
                  unsigned char passwordFlag, unsigned char usernameFlag, unsigned char *clientId,
                  unsigned char *willTopic, unsigned char *willMsg, unsigned char *username, unsigned char *password);

    unsigned char getCleanSession() const;

    unsigned char getWillFlag() const;

    unsigned char getWillQos() const;

    unsigned char getWillRetain() const;

    unsigned char getPasswordFlag() const;

    unsigned char getUsernameFlag() const;

    unsigned char *getClientId() const;

    unsigned char *getWillTopic() const;

    unsigned char *getWillMsg() const;

    unsigned char *getUsername() const;

    unsigned char *getPassword() const;

    unsigned char getProtocolLevel() const;

    unsigned char *getProtocolName() const;

    unsigned char getReservedBit() const;

    virtual ~ConnectPacket();

private:
    unsigned char protocolLevel;
    unsigned char *protocolName;
    unsigned char reservedBit;
    unsigned char cleanSession,
    unsigned char willFlag,
    unsigned char willQos,
    unsigned char willRetain,
    unsigned char passwordFlag,
    unsigned char usernameFlag,
    unsigned char *clientId,
    unsigned char *willTopic,
    unsigned char *willMsg,
    unsigned char *username,
    unsigned char *password

};

#endif //LMQTT__SERVER_CONNECTPACKET_H
