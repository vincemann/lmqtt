//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_CONNECTIONSESSION_H
#define LMQTT__SERVER_CONNECTIONSESSION_H


#include <list>
#include "../packets/RawPacket.h"

class ConnectionSession {

public:
    ConnectionSession();
    ~ConnectionSession();

    // todo add PacketIOManager as Friend, so he can call these methods
//private:
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsSent();
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived();
    std::list<RawPacket*>* _packets_sent;
    std::list<RawPacket*>* _packets_received;
};


#endif //LMQTT__SERVER_CONNECTIONSESSION_H
