//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_PACKETHANDLER_H
#define LMQTT__SERVER_PACKETHANDLER_H
#include "../packets/RawPacket.h"

template <class P>
class PacketHandler{
public:
    virtual void handle(P *pPacket) = 0;
};

#endif //LMQTT__SERVER_PACKETHANDLER_H
