//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H


#include <RawPacket.h>
#include "PacketHandler.h"

class ClientPublishPacketHandler : public PacketHandler {

    void handle(RawPacket *packet) override;
};


#endif //LMQTT__SERVER_CLIENTPUBLISHPACKETHANDLER_H
