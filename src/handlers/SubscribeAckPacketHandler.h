//
// Created by vince on 12.08.21.
//

#ifndef LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H
#define LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H


#include "PacketHandler.h"

class SubscribeAckPacketHandler : public PacketHandler{
public:
    SubscribeAckPacketHandler(PacketIOManager *packetIo);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_SUBSCRIBEACKPACKETHANDLER_H
