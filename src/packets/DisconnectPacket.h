//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_DISCONNECTPACKET_H
#define LMQTT__SERVER_DISCONNECTPACKET_H


#include "RawPacket.h"

class DisconnectPacket : public RawPacket{
public:
    DisconnectPacket();

    DisconnectPacket(RawPacket *rawPacket);
};


#endif //LMQTT__SERVER_DISCONNECTPACKET_H
