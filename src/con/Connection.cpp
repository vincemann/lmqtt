//
// Created by vince on 08.04.21.
//

#include "Connection.h"
#include <list>




//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packets_sent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packets_received;
//}



Connection::~Connection() {
    _packets_received->clear();
    _packets_sent->clear();
    delete _packets_received;
    delete _packets_sent;
}

Connection::Connection() {
    _packets_received= new std::list<RawPacket*>();
    _packets_sent= new std::list<RawPacket*>();
}
