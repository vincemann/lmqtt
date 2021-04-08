//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETIOMANAGER_H
#define LMQTT__SERVER_PACKETIOMANAGER_H

#include "../packets/RawPacket.h"
#include "parsers/PacketParser.h"
#include <map>

class PacketIOManager{
private:
//    struct Private;
    std::map<PacketType,PacketParser*> *_packet_parsers;
public:
    PacketIOManager(std::map<PacketType,PacketParser*> * parsers);

    //template<class P = const RawPacket&>
    virtual RawPacket* read_next(int socket_fd);
    void send(const RawPacket &packet, int socket_fd);
};



#endif //LMQTT__SERVER_PACKETIOMANAGER_H
