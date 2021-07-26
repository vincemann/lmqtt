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
#include <DisconnectPacketHandler.h>

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


int ConnectionManager::waitForConnection(int serverFd){
    int conn_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( _port );

    if ((conn_socket = accept(serverFd, (struct sockaddr *)&address,
            (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return conn_socket;
}

int ConnectionManager::bindToPort(){
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( _port );


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
    return server_fd;
}

void ConnectionManager::serveClients() {
    int serverFd = bindToPort();
    while (true){
        std::cout << "waiting for new connection" << "\n";
        int connFd = waitForConnection(serverFd);
        std::cout << "connected to client" << "\n";
        this->_clientConnected = 1;

        // INIT OBJECTS THAT LIVE AS LONG AS CLIENT IS CONNECTED
        ServerConnection* connection = new ServerConnection();
        PacketIOManager* packetIoManager = new PacketIOManager(connection, connFd, _parsers);
        FileDataManager* fileDataManager = new FileDataManager();
        ServerSessionRepository* serverSessionRepository = new ServerSessionRepository(fileDataManager);

        // HANDLERS
        std::map<PacketType,PacketHandler*> handlers;
        ConnectAckPacketFactory* connectAckPacketFactory = static_cast<ConnectAckPacketFactory*>(_factories->at(CONNACK));
        ConnectPacketHandler* connectPacketHandler = new ConnectPacketHandler(connection, packetIoManager, connectAckPacketFactory, serverSessionRepository);
        DisconnectPacketHandler* disconnectPacketHandler = new DisconnectPacketHandler(packetIoManager, this);
        handlers.insert(std::make_pair(CONNECT, connectPacketHandler));
        handlers.insert(std::make_pair(DISCONNECT, disconnectPacketHandler));


        while(true){
            try{
                std::cout << "waiting for new packet" << "\n";
                if (_clientConnected){
                    RawPacket* packet = packetIoManager->readPacket();
                    PacketHandler* handler = handlers[packet->getType()];
                    handler->handle(packet);
                    std::cout << "packet handled without errors" << "\n";
                } else{
                    // this is reached when disconnectClient() is called
                    break;
                }
            } catch (const std::exception& e) {
                std::cout << "exception occurred:" << "\n";
                std::cout << e.what() << "\n";
                break;
            }
        }

        printf("Client Disconnected\n");
        // CLIENT IS DISCONNECTED -> CLEANUP
        packetIoManager->closeConnection();
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
        delete packetIoManager;
    }
}

void ConnectionManager::disconnectClient() {
    printf("Disconnecting client\n");
    this->_clientConnected = 0;
}

ConnectionManager::ConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                                     std::map<PacketType, PacketFactory *> *factories) : _port(port), _parsers(parsers),
                                                                                         _factories(factories) {}

