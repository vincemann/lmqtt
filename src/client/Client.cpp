// Client side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include "../packets/ConnectPacket.h"
#include "../packets/PacketType.h"
#include "../io/PacketIOManager.h"
#include "../packets/factories/PacketFactory.h"
#include "../packets/factories/ConnectPacketFactory.h"
#include "../con/ClientConnectionSession.h"
#include "../handlers/ConnectAckPacketHandler.h"
#include "../packets/parsers/ConnAckPacketParser.h"

#define PORT 8080

static int connectToServer(){
    int conn_fd = 0;
    struct sockaddr_in serv_addr;
    if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if (connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    return conn_fd;
}


int main(int argc, char const *argv[])
{
    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnAckPacketParser* connAckPacketParser = new ConnAckPacketParser;
    parsers.insert(std::make_pair(CONNACK, connAckPacketParser));
    

    // FACTORIES
    ConnectPacketFactory* connectPacketFactory = new ConnectPacketFactory();
    int connFd = connectToServer();
    ClientConnectionSession *connection = new ClientConnectionSession();
    PacketIOManager* packetIo = new PacketIOManager(connection, connFd, &parsers);

    // HANDLERS
    std::map<PacketType,PacketHandler*> handlers;
    ConnectAckPacketHandler* connectAckPacketHandler = new ConnectAckPacketHandler(packetIo);
    handlers.insert(std::make_pair(CONNACK, connectAckPacketHandler));

    char* clientId = "niceClientId";
    char* username = "gil";
    char* password = "passw0rd";
    unsigned char cleanSession = 0;
    RawPacket* finConPacket = connectPacketFactory->create(cleanSession,clientId,username,password);
    packetIo->sendPacket(finConPacket);

    while (true){
        try{
            std::cout << "waiting for new packet" << "\n";
            RawPacket* packet = packetIo->readPacket();
            PacketHandler* handler = handlers[packet->getType()];
            handler->handle(packet);
            std::cout << "packet handled without errors" << "\n";
        } catch (const std::exception& e) {
            std::cout << "exception occurred:" << "\n";
            std::cout << e.what() << "\n";
            break;
        }
    }
    std::cout << "Closing Connection" << "\n";
    packetIo->closeConnection();
    delete connection;
    delete connectPacketFactory;
    return 0;
}