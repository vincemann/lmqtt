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
#include <SubscribePacketHandler.h>
#include <ServerPublishPacketHandler.h>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "handlers/PacketHandler.h"
#include "con/ServerConnection.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"

#include "ServerConnectionManager.h"


int ServerConnectionManager::waitForConnection(int serverFd){
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

int ServerConnectionManager::bindToPort(){
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

void ServerConnectionManager::serveClients() {
    int serverFd = bindToPort();
    while (true){
        std::cout << "waiting for new connection" << "\n";
        int connFd = waitForConnection(serverFd);
        std::cout << "_connected to client" << "\n";
        this->_clientConnected = 1;

        // INIT OBJECTS THAT LIVE AS LONG AS CLIENT IS CONNECTED
        ServerConnection* connection = new ServerConnection();
        topicRepository->setServerConnection(connection);
        PacketIOManager* packetIoManager = new PacketIOManager(connection, connFd, _parsers);

        // HANDLERS
        std::map<PacketType,PacketHandler*> handlers;
        ConnectAckPacketFactory* connectAckPacketFactory = static_cast<ConnectAckPacketFactory*>(_factories->at(CONNACK));
        ConnectPacketHandler* connectPacketHandler = new ConnectPacketHandler(connection, packetIoManager, connectAckPacketFactory, serverSessionRepository);

        DisconnectPacketHandler* disconnectPacketHandler = new DisconnectPacketHandler(packetIoManager, this);

        SubAckPacketFactory* subAckPacketFactory = static_cast<SubAckPacketFactory*>(_factories->at(SUBSCRIBE_ACK));
        SubscribePacketHandler* subscribePacketHandler = new SubscribePacketHandler(packetIoManager,
                                                                                    subAckPacketFactory, topicRepository);
        ServerPublishPacketHandler* serverPublishPacketHandler = new ServerPublishPacketHandler(packetIoManager,topicRepository);

        // todo maybe impl delegating packethandler that registers specific packethandlers
        handlers.insert(std::make_pair(CONNECT, connectPacketHandler));
        handlers.insert(std::make_pair(DISCONNECT, disconnectPacketHandler));
        handlers.insert(std::make_pair(SUBSCRIBE, subscribePacketHandler));
        handlers.insert(std::make_pair(PUBLISH, serverPublishPacketHandler));


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
                // if exception occurs close connection
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

        delete packetIoManager;
    }
}

void ServerConnectionManager::disconnectClient() {
    printf("Disconnecting client\n");
    this->_clientConnected = 0;
}

ServerConnectionManager::ServerConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                                                 std::map<PacketType, PacketFactory *> *factories,
                                                 ServerTopicRepository *topicRepository,
                                                 ServersClientInfoRepository *serverSessionRepository)
        : _port(port), _parsers(parsers),
          _factories(factories),  topicRepository(topicRepository),
          serverSessionRepository(serverSessionRepository) {}

