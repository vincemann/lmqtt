//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_PACKETHANDLER_H
#define LMQTT__SERVER_PACKETHANDLER_H

#include "../packets/RawPacket.h"
#include "../con/Connection.h"
#include "../io/PacketIOManager.h"


//todo add template
//template <class P>
class PacketHandler{
protected:
    PacketIOManager* _packetIo;
    void assertSpecificFlagsZero(RawPacket* packet);
public:
    explicit PacketHandler(PacketIOManager *packetIo);
    virtual void handle(RawPacket* packet) = 0;
    virtual ~PacketHandler();
};

#endif //LMQTT__SERVER_PACKETHANDLER_H
