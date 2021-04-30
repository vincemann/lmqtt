//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETIOMANAGER_H
#define LMQTT__SERVER_PACKETIOMANAGER_H

#include "../packets/RawPacket.h"
#include "parsers/PacketParser.h"
#include "../con/ConnectionSession.h"

#include <map>

class PacketIOManager{
public:
    PacketIOManager(ConnectionSession *session, int connFd, std::map<PacketType, PacketParser *> *packetParsers);

    //template<class P = const RawPacket&>
    virtual RawPacket* readPacket();
    void sendPacket(RawPacket *packet);
    void closeConnection();
    // only packet io manager can write to these lists

private:
//    struct Private;
    int _conn_fd;
    ConnectionSession *_connectionSession;
    std::map<PacketType,PacketParser*>* _packet_parsers;
};



#endif //LMQTT__SERVER_PACKETIOMANAGER_H
