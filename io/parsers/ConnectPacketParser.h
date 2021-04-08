//
// Created by vince on 06.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETPARSER_H
#define LMQTT__SERVER_CONNECTPACKETPARSER_H

#include "../../packets/ConnectPacket.h"
#include "../../packets/RawPacket.h"
#include "PacketParser.h"

class ConnectPacketParser : public PacketParser/*<ConnectPacket>*/{
public:
//    ConnectPacket* parse(RawPacket* raw_packet);
    RawPacket* parse(RawPacket* raw_packet);
};


#endif //LMQTT__SERVER_CONNECTPACKETPARSER_H
