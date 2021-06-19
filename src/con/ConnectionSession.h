//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_CONNECTIONSESSION_H
#define LMQTT__SERVER_CONNECTIONSESSION_H


#include <list>
#include "../packets/RawPacket.h"
#include "../session/Session.h"


class ConnectionSession {

public:
    ConnectionSession(int conn_fd);
    ~ConnectionSession();

    std::list<RawPacket *>* getPacketsSent();
    std::list<RawPacket *>* getPacketsReceived();

    // todo add PacketIOManager as Friend, so he can call these methods
//private:
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsSent();
//    friend std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived();
    std::list<RawPacket*>* _packets_sent;
    std::list<RawPacket*>* _packets_received;
    Session *_session;

};


#endif //LMQTT__SERVER_CONNECTIONSESSION_H
