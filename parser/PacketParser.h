//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETPARSER_H
#define LMQTT__SERVER_PACKETPARSER_H

#include "../packets/RawPacket.h"
#include "../packet_factories/ConnectPacketFactory.h"
#include <map>

class PacketParser{
private:
//    struct Private;
    std::map<PacketType,ConnectPacketFactory*> *_packet_factories;
public:
    PacketParser(std::map<PacketType,ConnectPacketFactory*> * factories);

    //template<class P = const RawPacket&>
    virtual RawPacket* read_next(int socket_fd);
};



#endif //LMQTT__SERVER_PACKETPARSER_H
