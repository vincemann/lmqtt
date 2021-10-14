//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHPACKET_H
#define LMQTT__SERVER_PUBLISHPACKET_H


#include "RawPacket.h"

class PublishPacket : public RawPacket{
    unsigned char dupFlag;
    unsigned short qos;
    unsigned char retainFlag;
    char* topic;
    long int packetId;
    char* msg;

public:
    PublishPacket(RawPacket *rawPacket, unsigned char dupFlag, unsigned short qos,
                  unsigned char retainFlag, char *topic, long int packetId, char *msg);

    unsigned char getDupFlag() const;

    unsigned short getQos() const;

    unsigned char getRetainFlag() const;

    char *getTopic() const;

    long int getPacketId() const;

    char *getMsg() const;
};


#endif //LMQTT__SERVER_PUBLISHPACKET_H
