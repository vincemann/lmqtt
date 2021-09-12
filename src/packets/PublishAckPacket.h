//
// Created by vince on 12.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHACKPACKET_H
#define LMQTT__SERVER_PUBLISHACKPACKET_H


#include "RawPacket.h"

class PublishAckPacket : public RawPacket{
    unsigned long packetId;
public:
    PublishAckPacket(RawPacket *rawPacket, unsigned long packetId);

    unsigned long getPacketId() const;
};


#endif //LMQTT__SERVER_PUBLISHACKPACKET_H
