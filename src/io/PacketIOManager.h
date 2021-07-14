//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETIOMANAGER_H
#define LMQTT__SERVER_PACKETIOMANAGER_H

#include "../packets/RawPacket.h"
#include "../packets/parsers/PacketParser.h"
#include "../con/Connection.h"

#include <map>

class PacketIOManager{
private:
    unsigned int evalPacketLength();
public:
    PacketIOManager(Connection *session, int connFd, std::map<PacketType, PacketParser *> *packetParsers);
    PacketIOManager();

    //template<class P = const RawPacket&>
    virtual RawPacket* readPacket();
    void sendPacket(RawPacket *packet);
    void closeConnection();
    // only packet io manager can write to these lists
    int _connFd;
    Connection *_connectionSession;
    std::map<PacketType,PacketParser*>* _packetParsers;


};



#endif //LMQTT__SERVER_PACKETIOMANAGER_H
