//
// Created by derdoc on 7/4/21.
//
// APPROVED V2

#ifndef LMQTT__SERVER_SUBSCRIBEPACKETPARSER_H
#define LMQTT__SERVER_SUBSCRIBEPACKETPARSER_H

#include "../SubscribePacket.h"
#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"

class SubscribePacketParser : public PacketParser{
public:
    RawPacket* parse(RawPacket* pRawPacket);

};


#endif //LMQTT__SERVER_SUBSCRIBEPACKETPARSER_H
