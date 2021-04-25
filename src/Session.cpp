//
// Created by vince on 08.04.21.
//

#include "Session.h"
#include <list>




//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packets_sent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packets_received;
//}


std::list<RawPacket *>* Session::getPacketsSent() {
    return _packets_sent;
}

std::list<RawPacket *>* Session::getPacketsReceived() {
    return _packets_received;
}
