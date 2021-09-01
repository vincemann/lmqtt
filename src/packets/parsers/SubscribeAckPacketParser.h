//
// Created by vince on 02.09.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEACKPACKETPARSER_H
#define LMQTT__SERVER_SUBSCRIBEACKPACKETPARSER_H


#include <PacketHandler.h>

class SubscribeAckPacketParser : public  PacketParser{
public:
    RawPacket *parse(RawPacket *raw_packet) override;

};


#endif //LMQTT__SERVER_SUBSCRIBEACKPACKETPARSER_H
