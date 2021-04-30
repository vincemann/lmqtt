//
// Created by vince on 08.04.21.
//

#include "ConnectionSession.h"
#include <list>




//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packets_sent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packets_received;
//}


std::list<RawPacket *>* ConnectionSession::getPacketsSent() {
    return _packets_sent;
}

std::list<RawPacket *>* ConnectionSession::getPacketsReceived() {
    return _packets_received;
}


ConnectionSession::~ConnectionSession() {
    _packets_received->clear();
    _packets_sent->clear();
    delete _packets_received;
    delete _packets_sent;
    delete _session;
}

ConnectionSession::ConnectionSession(int conn_fd) {
    _packets_received= new std::list<RawPacket*>();
    _packets_sent= new  std::list<RawPacket*>();
}
