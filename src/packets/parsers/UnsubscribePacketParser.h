//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBSCRIBEPACKETPARSER_H
#define LMQTT__SERVER_UNSUBSCRIBEPACKETPARSER_H

#include <PacketHandler.h>

class UnsubscribePacketParser : public  PacketParser{
public:
    RawPacket *parse(RawPacket *raw_packet) override;

};


#endif //LMQTT__SERVER_UNSUBSCRIBEPACKETPARSER_H
