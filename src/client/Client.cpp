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
#include "../io/PacketIOManager.h"
#include "../packets/factories/ConnectPacketFactory.h"
#include "../con/ClientConnectionSession.h"
#include "../handlers/ConnectAckPacketHandler.h"
#include "../packets/parsers/ConnAckPacketParser.h"

//#define PORT 8080

char* IP = 0;
int PORT = 0;

static int connectToServer() {
    int conn_fd = 0;
    struct sockaddr_in serv_addr;
    if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address/ Address not supported \n");
        exit(1);
    }

    if (connect(conn_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        exit(1);
    }
    return conn_fd;
}

static void attemptConnection(RawPacket *connectPacket, PacketIOManager *packetIoManager,
                              ConnectAckPacketHandler *connectAckPacketHandler,
                              ClientConnectionSession* connection,
                              std::map<PacketType, PacketParser *>* parsers) {
    int connFd = connectToServer();
    packetIoManager = new PacketIOManager(connection, connFd, parsers);
    std::cout << "Sending Connect packet" << "\n";
    packetIoManager->sendPacket(connectPacket);
    std::cout << "waiting for ConnAck packet" << "\n";
    RawPacket *packet = packetIoManager->readPacket();
    if (packet->getType() != CONNACK) {
        throw MsgException("Did not recv Connack packet, terminating");
    }
    connectAckPacketHandler->handle(packet);
    std::cout << "connack packet handled without errors" << "\n";
}

enum CLIMode{ CONNECT_MODE, SUBSCRIBE_MODE, PUBLISH_MODE, RECV_MODE } mode;

static CLIMode findCliMode(char *argv[]){
    char* firstArg = argv[1];
    if (strcmp("connect",firstArg) == 0){
        return CONNECT_MODE;
    }
    fprintf(stderr,"%s","Invalid cli mode");
    exit(1);
}

static void printUsageInformation(char* progName){
    switch (mode) {
        case CONNECT_MODE:
            fprintf(stderr, "Usage: %s [-c -u -p -i [-r] ] ip port\n", progName);
    }

}

static void initRoute(char *argv[]){
    IP = argv[optind];
    PORT = strtol(argv[optind+1],nullptr,10);
    printf("route: %s:%d\n",IP,PORT);
}

int main(int argc, char *argv[]) {
    // PARSERS
    std::map<PacketType, PacketParser *> parsers;
    ConnAckPacketParser *connAckPacketParser = new ConnAckPacketParser;
    parsers.insert(std::make_pair(CONNACK, connAckPacketParser));

    // FACTORIES
    ConnectPacketFactory*  connectPacketFactory = new ConnectPacketFactory();

    ClientConnectionSession *connection = new ClientConnectionSession();

    // gets initialized by attemptConnection
    PacketIOManager *packetIoManager;

    // HANDLERS
    std::map<PacketType, PacketHandler *> handlers;
    ConnectAckPacketHandler *connectAckPacketHandler = new ConnectAckPacketHandler(packetIoManager);
    handlers.insert(std::make_pair(CONNACK, connectAckPacketHandler));


    mode = findCliMode(argv);
    optind = 2;

    char *clientId = 0;
    char *username = 0;
    char *password = 0;
    unsigned char cleanSession = 0;

    switch (mode) {
        case CONNECT_MODE:
            int opt;
            // i = clientId, u = username, p = password, r=removeSession
            //todo learn to make args obsolete (i is needed, i think it was '!' or smth)
            while ((opt = getopt(argc, argv, "u:p:i:r")) != -1) {
                switch (opt) {
                    case 'u': username = optarg; break;
                    case 'p': password = optarg; break;
                    case 'i': clientId = optarg; break;
                    case 'r': cleanSession=1; break;
                    default: /* '?' */
                        printUsageInformation( argv[0]);
                        exit(1);
                }
            }
            initRoute(argv);
            if (clientId == 0){
                fprintf(stderr, "Client Id missing");
                printUsageInformation( argv[0]);
                exit(1);
            }
            RawPacket *connectPacket = connectPacketFactory->create(cleanSession, clientId, username, password);
            try {
                attemptConnection(connectPacket, packetIoManager, connectAckPacketHandler,connection,&parsers);
                std::cout << "Successfully connected to Server!" << "\n";
                exit(0);
            } catch (const std::exception &e) {
                std::cout << "exception occurred while creating connection with server:" << "\n";
                std::cout << e.what() << "\n";
                exit(1);
            }
    };

    // todo useful for publishing msges later
    /* Process file names or stdin */
//    if (optind >= argc)
//        process(stdin, "(standard input)", op_mode);
//    else
//    {
//        int i;
//        for (i = optind; i < argc; i++)
//        {
//            FILE *fp = fopen(argv[i], "r");
//            if (fp == 0)
//                fprintf(stderr, "%s: failed to open %s (%d %s)\n",
//                        argv[0], argv[i], errno, strerror(errno));
//            else
//            {
//                process(fp, argv[i], op_mode);
//                fclose(fp);
//            }
//        }
//    }



//    while (true) {
//        try {
//            std::cout << "waiting for new packet" << "\n";
//            RawPacket *packet = packetIoManager->readPacket();
//            PacketHandler *handler = handlers[packet->getType()];
//            handler->handle(packet);
//            std::cout << "packet handled without errors" << "\n";
//        } catch (const std::exception &e) {
//            std::cout << "exception occurred:" << "\n";
//            std::cout << e.what() << "\n";
//            break;
//        }
//    }
    std::cout << "Closing Connection" << "\n";
    packetIoManager->closeConnection();
    return 0;
}