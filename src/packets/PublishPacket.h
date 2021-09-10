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
    unsigned short packetId;
    char* msg;

public:
    PublishPacket(RawPacket *rawPacket, unsigned char dupFlag, unsigned short qos, unsigned char retainFlag,
                  char *topic, unsigned short packetId, char *msg);
};


#endif //LMQTT__SERVER_PUBLISHPACKET_H
