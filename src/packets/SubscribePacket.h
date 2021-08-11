//
// Created by derdoc on 7/4/21.
//
// dessen gil

#ifndef LMQTT__SERVER_SUBSCRIBEPACKET_H
#define LMQTT__SERVER_SUBSCRIBEPACKET_H

#include "RawPacket.h"

class SubscribePacket : public RawPacket{
public:

    SubscribePacket(RawPacket *rawPacket, unsigned short packetId, char *topic, unsigned char qos);

    unsigned short getPacketId() const;

    char *getTopic() const;

    unsigned char getQos() const;

    virtual ~SubscribePacket();
private:
    // todo remove array initialisations
    // todo add leading _ for member vars
    unsigned short _packetId;
    char *topic;

    unsigned short qos;
};


#endif //LMQTT__SERVER_SUBSCRIBEPACKET_H
