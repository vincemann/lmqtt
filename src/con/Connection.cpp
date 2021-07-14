//
// Created by vince on 08.04.21.
//

#include "Connection.h"
#include <list>




//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packetsSent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packetsReceived;
//}



Connection::~Connection() {
    // packets will not be removed from heap
    _packetsReceived->clear();
    _packetsSent->clear();
    delete _packetsReceived;
    delete _packetsSent;
}

Connection::Connection() {
    _packetsReceived= new std::list<RawPacket*>();
    _packetsSent= new std::list<RawPacket*>();
}
