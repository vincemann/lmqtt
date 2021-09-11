//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBACKPACKETPARSER_H
#define LMQTT__SERVER_UNSUBACKPACKETPARSER_H

#include <PacketHandler.h>
#include "../RawPacket.h"
#include "PacketParser.h"

class UnsubAckPacketParser : public  PacketParser{
public:
    RawPacket *parse(RawPacket* raw_packet) override;

};


#endif //LMQTT__SERVER_UNSUBACKPACKETPARSER_H
