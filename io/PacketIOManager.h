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
    std::list<RawPacket*> _packets_sent;
    std::list<RawPacket*> _packets_received;
    int _conn_fd;
    std::map<PacketType,PacketParser*> *_packet_parsers;
public:
    PacketIOManager(std::map<PacketType,PacketParser*> * parsers, int conn_fd);

    //template<class P = const RawPacket&>
    virtual RawPacket* read_packet();
    void send_packet(const RawPacket &packet);
    // only packet io manager can write to these lists
    const std::list<RawPacket *> &getPacketsSent() const;
    const std::list<RawPacket *> &getPacketsReceived() const;
};



#endif //LMQTT__SERVER_PACKETIOMANAGER_H
