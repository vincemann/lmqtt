//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CLIENTCONNECTIONMANAGER_H
#define LMQTT__SERVER_CLIENTCONNECTIONMANAGER_H

#include <PacketParser.h>
#include <PacketIOManager.h>
#include <ConnectAckPacketHandler.h>
#include "ClientConnectionManager.h"
#include "../topic/ClientTopicRepository.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <DisconnectPacket.h>


class ClientConnectionManager {
public:
    // need to be set via setters
    char _connected = 0;
    char* _ip;
    int _port;
    PacketIOManager *packetIoManager;
    ConnectAckPacketHandler *_connectAckPacketHandler;
    ClientConnection *_connection;
    ClientTopicRepository* clientTopicRepository;
    std::map<PacketType, PacketParser *> *parsers;
    std::map<PacketType, PacketHandler *>* handlers;

    ClientConnectionManager(PacketIOManager *packetIoManager,
                            ConnectAckPacketHandler *connectAckPacketHandler,
                            ClientConnection *connection,
                            std::map<PacketType, PacketParser *> *parsers,
                            std::map<PacketType, PacketHandler *> *handlers,
                            ClientTopicRepository *clientTopicRepository);

    void attemptConnection(RawPacket *rawPacket);
    int connectToServer();
    void handleIncomingPackets();
    void closeConnection();
    void setIp(char *ip);
    void setPort(int port);
};


#endif //LMQTT__SERVER_CLIENTCONNECTIONMANAGER_H
