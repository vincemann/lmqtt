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



ConnectionSession::~ConnectionSession() {
    _packets_received->clear();
    _packets_sent->clear();
    delete _packets_received;
    delete _packets_sent;
}

ConnectionSession::ConnectionSession() {
    _packets_received= new std::list<RawPacket*>();
    _packets_sent= new std::list<RawPacket*>();
}
