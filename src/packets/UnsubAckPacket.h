//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBACKPACKET_H
#define LMQTT__SERVER_UNSUBACKPACKET_H


#include "RawPacket.h"

class UnsubAckPacket : public RawPacket{
    unsigned short _packetId;
public:
    UnsubAckPacket(RawPacket *rawPacket, unsigned short packetId);

    unsigned short getPacketId() const;
};


#endif //LMQTT__SERVER_UNSUBACKPACKET_H
