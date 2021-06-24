//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTACKPACKETHANDLER_H

#include "PacketHandler.h"

class ConnectAckPacketHandler : public PacketHandler{
public:
    explicit ConnectAckPacketHandler(PacketIOManager *packetIo);
    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
