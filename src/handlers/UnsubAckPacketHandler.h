//
// Created by archdoc on 10/09/2021.
//

#ifndef LMQTT__SERVER_UNSUBACKPACKETHANDLER_H
#define LMQTT__SERVER_UNSUBACKPACKETHANDLER_H


#include <ClientConnection.h>
#include "PacketHandler.h"

class UnsubAckPacketHandler : public PacketHandler{
public:
    explicit UnsubAckPacketHandler(PacketIOManager *packetIo);
    void handle(RawPacket *rawPacket) override;
};


#endif //LMQTT__SERVER_UNSUBACKPACKETHANDLER_H
