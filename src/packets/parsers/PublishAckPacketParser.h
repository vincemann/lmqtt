//
// Created by vince on 13.10.21.
//

#ifndef LMQTT__SERVER_PUBLISHACKPACKETPARSER_H
#define LMQTT__SERVER_PUBLISHACKPACKETPARSER_H


#include "PacketParser.h"

class PublishAckPacketParser : public PacketParser{
public:
    RawPacket *parse(RawPacket *raw_packet) override;
};


#endif //LMQTT__SERVER_PUBLISHACKPACKETPARSER_H
