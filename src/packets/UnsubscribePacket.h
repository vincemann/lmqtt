//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKET_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKET_H

#include "RawPacket.h"

class UnsubscribePacket : public RawPacket{
public:

    UnsubscribePacket(RawPacket *rawPacket, unsigned short packetId, char *topic);

    unsigned short getPacketId() const;

    char *getTopic() const;

    virtual ~UnsubscribePacket();
private:
    unsigned short _packetId;
    char *topic;


};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKET_H
