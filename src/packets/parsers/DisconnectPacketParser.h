//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_DISCONNECTPACKETPARSER_H
#define LMQTT__SERVER_DISCONNECTPACKETPARSER_H


#include "PacketParser.h"

class DisconnectPacketParser : public PacketParser{
public:
    RawPacket* parse(RawPacket* rawPacket) override;
};


#endif //LMQTT__SERVER_DISCONNECTPACKETPARSER_H
