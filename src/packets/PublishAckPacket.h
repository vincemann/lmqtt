//
// Created by vince on 12.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHACKPACKET_H
#define LMQTT__SERVER_PUBLISHACKPACKET_H


#include "RawPacket.h"

class PublishAckPacket : public RawPacket{
    long int packetId;
public:
    PublishAckPacket(RawPacket *rawPacket, long int packetId);

    long int getPacketId() const;
};


#endif //LMQTT__SERVER_PUBLISHACKPACKET_H
