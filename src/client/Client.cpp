// Client side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <DisconnectPacket.h>
#include <SubscribePacketParser.h>
#include <SubscribeAckPacketParser.h>
#include <SubscribeAckPacketHandler.h>


#include "../io/PacketIOManager.h"
#include "../packets/factories/ConnectPacketFactory.h"
#include "../con/ClientConnection.h"
#include "../handlers/ConnectAckPacketHandler.h"
#include "../packets/parsers/ConnAckPacketParser.h"
#include "./mode/CLIMode.h"
#include "mode/ConnectCLIModeHandler.h"
#include "ClientConnectionManager.h"
#include "mode/SubscribeCLIModeHandler.h"


static void createSessionDirectories() {
    const char *targetDir = "/.lmqtt/client/sessions";
    char *home = getenv("HOME");
    char *dir = (char *) malloc(strlen(home) + strlen(targetDir) + 1);
    strcpy(dir, home);
    strcat(dir, "/.lmqtt");
    Utils::createDirectory(dir);
    strcat(dir, "/client");
    Utils::createDirectory(dir);
    strcat(dir, "/sessions");
    Utils::createDirectory(dir);
}


int main(int argc, char *argv[]) {
    createSessionDirectories();
    // PARSERS
    std::map<PacketType, PacketParser *> parsers;
    ConnAckPacketParser *connAckPacketParser = new ConnAckPacketParser;
    parsers.insert(std::make_pair(CONNACK, connAckPacketParser));
    SubscribeAckPacketParser *subscribePacketParser = new SubscribeAckPacketParser;
    parsers.insert(std::make_pair(SUBSCRIBE_ACK, subscribePacketParser));

    // FACTORIES
    ConnectPacketFactory *connectPacketFactory = new ConnectPacketFactory();
    SubscribePacketFactory *subscribePacketFactory = new SubscribePacketFactory();


    FileDataManager *fileDataManager = new FileDataManager();
    ClientConnection *connection = new ClientConnection();
    ClientSessionRepository *clientSessionRepository = new ClientSessionRepository(fileDataManager);

    // gets initialized by attemptConnection
    PacketIOManager *packetIoManager = new PacketIOManager();



    // HANDLERS
    std::map<PacketType, PacketHandler *> handlers;
    ConnectAckPacketHandler *connectAckPacketHandler = new ConnectAckPacketHandler(packetIoManager,
                                                                                   clientSessionRepository, connection);

    SubscribeAckPacketHandler* subscribeAckPacketHandler = new SubscribeAckPacketHandler(packetIoManager,connection);


    handlers.insert(std::make_pair(CONNACK, connectAckPacketHandler));
    handlers.insert(std::make_pair(SUBSCRIBE_ACK, subscribeAckPacketHandler));



    // CONNECTION PROCESS ENCAPSULATED
    ClientConnectionManager *clientConnectionManager = new ClientConnectionManager(packetIoManager,
                                                                                   connectAckPacketHandler, connection,
                                                                                   &parsers,&handlers);

    // MODE HANDLERS
    CLIMode mode = CLIModes::findCliMode(argv[1]);
    optind = 2;


    switch (mode) {
        case CONNECT_MODE: {
            printf("connect mode\n");
            ConnectCLIModeHandler *connectCliModeHandler = new ConnectCLIModeHandler(argv, clientConnectionManager,
                                                                                     connectPacketFactory, argc);
            connectCliModeHandler->handle();
            break;
        }

        case SUBSCRIBE_MODE: {
            printf("subscribe mode\n");
            SubscribeCLIModeHandler *subscribeCliModeHandler = new SubscribeCLIModeHandler(argv,
                                                                                           clientConnectionManager,
                                                                                           connectPacketFactory, argc,
                                                                                           clientSessionRepository,
                                                                                           subscribePacketFactory,subscribeAckPacketHandler);
            subscribeCliModeHandler->handle();
            break;
        }
    };

    // todo useful for publishing msges later
    /* Process file names or stdin */
//    if (optind >= _argc)
//        process(stdin, "(standard input)", op_mode);
//    else
//    {
//        int i;
//        for (i = optind; i < _argc; i++)
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
//            RawPacket *packet = _packetIoManager->readPacket();
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