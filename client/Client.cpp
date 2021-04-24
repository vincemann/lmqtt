// Client side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../packets/ConnectPacket.h"
#include "../packets/PacketType.h"
#include "../io/PacketIOManager.h"
#include "../packets/factories/PacketFactory.h"
#include "../packets/factories/ConnectPacketFactory.h"


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
    std::map<PacketType,PacketParser*> parsers;
    std::map<PacketType,PacketFactory*> factories;

    ConnectPacketFactory connectPacketFactory;
    factories.insert(std::make_pair(CONNECT, &connectPacketFactory));

    int conn_fd = connectToServer();
    PacketIOManager packetIoManager (&parsers, conn_fd);

    char* data = "connect me pls";
    char* clientId = "niceClientId";
    char* username = "gil";
    char* password = "passw0rd"
    RawPacket* finConPacket = connectPacketFactory.create(0,clientId,username,password);
    packetIoManager.sendPacket(finConPacket);
    return 0;
}