//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_PACKETHANDLER_H
#define LMQTT__SERVER_PACKETHANDLER_H

#include "../packets/RawPacket.h"
#include "../con/ConnectionSession.h"
#include "../io/PacketIOManager.h"


//todo add template
//template <class P>
class PacketHandler{
public:
    PacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo);

//    virtual void handle(P* packet) = 0;
    virtual void handle(RawPacket* packet) = 0;
protected:
    ConnectionSession* _connectionSession;
    PacketIOManager* _packetIo;
};

#endif //LMQTT__SERVER_PACKETHANDLER_H
