//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETRECEIVER_H
#define LMQTT__SERVER_PACKETRECEIVER_H

#include "../packets/RawPacket.h"
#include "factories/ConnectPacketFactory.h"
#include <map>

class PacketReceiver{
private:
//    struct Private;
    std::map<PacketType,ConnectPacketFactory*> *_packet_factories;
public:
    PacketReceiver(std::map<PacketType,ConnectPacketFactory*> * factories);

    //template<class P = const RawPacket&>
    virtual RawPacket* read_next(int socket_fd);
};



#endif //LMQTT__SERVER_PACKETRECEIVER_H
