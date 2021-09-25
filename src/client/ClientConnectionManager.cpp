//
// Created by vince on 25.07.21.
//

#include <PacketParser.h>
#include <PacketIOManager.h>
#include <ConnectAckPacketHandler.h>
#include "ClientConnectionManager.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <DisconnectPacket.h>


void ClientConnectionManager::attemptConnection(RawPacket *connectPacket) {
    int connFd = connectToServer();
    _packetIoManager->_connFd = connFd;
    _packetIoManager->_connectionSession = _connection;
    _packetIoManager->_packetParsers = parsers;

    std::cout << "Sending Connect packet" << "\n";
    _packetIoManager->sendPacket(connectPacket);
    std::cout << "waiting for ConnAck packet" << "\n";
    RawPacket *packet = _packetIoManager->readPacket();
    if (packet->getType() != CONNACK) {
        throw MsgException("Did not recv Connack packet, terminating");
    }
    _connectAckPacketHandler->handle(packet);
    std::cout << "connack packet handled without errors" << "\n";
    std::cout << "Successfully _connected to Server!" << "\n";
}

int ClientConnectionManager::connectToServer() {
    int conn_fd;
    struct sockaddr_in serv_addr;
    if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, _ip, &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address/ Address not supported \n");
        exit(1);
    }

    if (connect(conn_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        exit(1);
    }
    _connected=1;
    return conn_fd;
}



ClientConnectionManager::ClientConnectionManager(PacketIOManager *packetIoManager,
                                                 ConnectAckPacketHandler *connectAckPacketHandler,
                                                 ClientConnection *connection,
                                                 std::map<PacketType, PacketParser *> *parsers, std::map<PacketType, PacketHandler *>* handlers) : _packetIoManager(
        packetIoManager), _connectAckPacketHandler(connectAckPacketHandler), _connection(connection), parsers(parsers), handlers(handlers) {}

void ClientConnectionManager::setIp(char *ip) {
    _ip = ip;
}

void ClientConnectionManager::setPort(int port) {
    _port = port;
}

void ClientConnectionManager::closeConnection() {
    _packetIoManager->sendPacket(new DisconnectPacket());
    _packetIoManager->closeConnection();
    _connected = 0;
}

void ClientConnectionManager::handleIncomingPackets() {
    while(true){
        try{
            std::cout << "waiting for new packet" << "\n";
            if (_connected){
                RawPacket* packet = _packetIoManager->readPacket();
                PacketHandler* handler = handlers->at(packet->getType());
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
}

