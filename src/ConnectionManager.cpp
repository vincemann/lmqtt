//
// Created by vince on 14.07.21.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "handlers/PacketHandler.h"
#include "con/ServerConnection.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"

#include "ConnectionManager.h"

int ConnectionManager::waitForConnection(){
    int server_fd, conn_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( _port );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
            sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((conn_socket = accept(server_fd, (struct sockaddr *)&address,
            (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return conn_socket;
}

void ConnectionManager::serveClients() {
    while (true){
        std::cout << "waiting for new connection" << "\n";
        int connFd = waitForConnection();
        std::cout << "connected to client" << "\n";
        this->_clientConnected = 1;

        // INIT OBJECTS THAT LIVE AS LONG AS CLIENT IS CONNECTED
        ServerConnection* connection = new ServerConnection();
        PacketIOManager* packetIO = new PacketIOManager(connection,connFd, _parsers);
        FileDataManager* fileDataManager = new FileDataManager();

        // HANDLERS
        std::map<PacketType,PacketHandler*> handlers;
        ServerSessionRepository* serverSessionRepository = new ServerSessionRepository(fileDataManager);
        ConnectAckPacketFactory* connectAckPacketFactory = static_cast<ConnectAckPacketFactory*>(_factories->at(CONNACK));
        ConnectPacketHandler* connectPacketHandler = new ConnectPacketHandler(connection,packetIO,connectAckPacketFactory, serverSessionRepository);
        handlers.insert(std::make_pair(CONNECT, connectPacketHandler));


        while(true){
            try{
                std::cout << "waiting for new packet" << "\n";
                if (_clientConnected){
                    RawPacket* packet = packetIO->readPacket();
                    PacketHandler* handler = handlers[packet->getType()];
                    handler->handle(packet);
                    std::cout << "packet handled without errors" << "\n";
                } else{
                    break;
                }
            } catch (const std::exception& e) {
                std::cout << "exception occurred:" << "\n";
                std::cout << e.what() << "\n";
                break;
            }
        }

        // CLIENT IS DISCONNECTED -> CLEANUP
        packetIO->closeConnection();
        for (const auto &packet : *connection->_packetsSent){
            delete packet;
        }
        for (const auto &packet : *connection->_packetsReceived){
            delete packet;
        }
        delete connection;

        for (const auto& any : handlers) {
            delete any.second;
        }

        delete serverSessionRepository;
        delete fileDataManager;
        delete packetIO;
    }
}

void ConnectionManager::disconnectClient() {
    this->_clientConnected = 0;
}

ConnectionManager::ConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                                     std::map<PacketType, PacketFactory *> *factories) : _port(port), _parsers(parsers),
                                                                                         _factories(factories) {}

