//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHPACKETPARSER_H
#define LMQTT__SERVER_PUBLISHPACKETPARSER_H


#include "PacketParser.h"

class PublishPacketParser : public PacketParser{
public:
    RawPacket *parse(RawPacket *raw_packet) override;
};


#endif //LMQTT__SERVER_PUBLISHPACKETPARSER_H
