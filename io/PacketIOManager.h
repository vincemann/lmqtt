//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETIOMANAGER_H
#define LMQTT__SERVER_PACKETIOMANAGER_H

#include "../packets/RawPacket.h"
#include "parsers/PacketParser.h"
#include "../Session.h"

#include <map>

class PacketIOManager{
public:
    PacketIOManager(Session *session, int connFd, std::map<PacketType, PacketParser *> *packetParsers);

    //template<class P = const RawPacket&>
    virtual RawPacket* read_packet();
    void send_packet(RawPacket *packet);
    // only packet io manager can write to these lists

private:
//    struct Private;
    Session* _session;
    int _conn_fd;
    std::map<PacketType,PacketParser*>* _packet_parsers;
};



#endif //LMQTT__SERVER_PACKETIOMANAGER_H
