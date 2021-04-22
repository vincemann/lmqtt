//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_PACKETHANDLER_H
#define LMQTT__SERVER_PACKETHANDLER_H
#include "../packets/RawPacket.h.h"
#include "../Session.h"


//todo add template
//template <class P>
class PacketHandler{
public:
    PacketHandler(const Session &session);

//    virtual void handle(P* packet) = 0;
    virtual void handle(RawPacket* packet) = 0;

protected:
    Session _session;
};

#endif //LMQTT__SERVER_PACKETHANDLER_H
