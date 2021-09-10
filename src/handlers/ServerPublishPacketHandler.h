//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
#define LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H


#include "PacketHandler.h"

class ServerPublishPacketHandler : public PacketHandler{

public:
    void handle(RawPacket *packet) override;

};


#endif //LMQTT__SERVER_SERVERPUBLISHPACKETHANDLER_H
