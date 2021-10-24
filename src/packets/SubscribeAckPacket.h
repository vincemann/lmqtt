//
// Created by vince on 11.08.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEACKPACKET_H
#define LMQTT__SERVER_SUBSCRIBEACKPACKET_H


#include "RawPacket.h"

class SubscribeAckPacket : public RawPacket{
    int _packetId;
    unsigned char _retCode;

public:
    SubscribeAckPacket(RawPacket *rawPacket, int packetId, unsigned char retCode);

    int getPacketId() const;

    unsigned char getRetCode() const;
};


#endif //LMQTT__SERVER_SUBSCRIBEACKPACKET_H
