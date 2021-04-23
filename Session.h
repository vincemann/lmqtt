//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

#include "io/PacketIOManager.h"

#include <list>

class Session {

public:
    std::list<RawPacket *> *getPacketsSent() const;
    std::list<RawPacket *> *getPacketsReceived() const;

    // todo add PacketIOManager as Friend, so he can call these methods
private:
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsSent();
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived();
    std::list<RawPacket*>* _packets_sent;
    std::list<RawPacket*>* _packets_received;

};


#endif //LMQTT__SERVER_SESSION_H
