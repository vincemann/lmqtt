#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "parser/PacketReceiver.h"
#include "packets/ConnectPacket.h"
#include "parser/factories/ConnectPacketFactory.h"
#include "packet_handlers/ConnectPacketHandler.h"

#define PORT 8080
int main(int argc, char const *argv[])
{
    std::map<PacketType,ConnectPacketFactory*> factories;
    ConnectPacketFactory* connect_packet_factory = new ConnectPacketFactory;
    factories.insert(std::make_pair(CONNECT,connect_packet_factory));
    ConnectPacketHandler* connect_packet_handler = new ConnectPacketHandler;


    PacketReceiver* parser = new PacketReceiver(&factories);

    int server_fd, conn_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *answer = "Packet received";

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
    address.sin_port = htons( PORT );

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
    ConnectPacket* con_packet = dynamic_cast<ConnectPacket*>(parser->read_next(conn_socket));
    connect_packet_handler->handle(con_packet);

    send(conn_socket , answer , strlen(answer) , 0 );
    return 0;
}