//
// Created by vince on 08.04.21.
//

#include "Session.h"
#include <list>


const std::list<RawPacket *> *Session::getPacketsSent() const {
    return _packets_sent;
}

const std::list<RawPacket *> *Session::getPacketsReceived() const {
    return _packets_received;
}

//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packets_sent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packets_received;
//}


