//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKET_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKET_H

#include "RawPacket.h"

class UnsubscribePacket : public RawPacket{
public:

    UnsubscribePacket(RawPacket *rawPacket, int packetId, char *topic);

    int getPacketId() const;

    char *getTopic() const;

    ~UnsubscribePacket();
private:
    int _packetId;
    char *topic;


};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKET_H
