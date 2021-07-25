// Client side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <DisconnectPacket.h>


#include "../io/PacketIOManager.h"
#include "../packets/factories/ConnectPacketFactory.h"
#include "../con/ClientConnection.h"
#include "../handlers/ConnectAckPacketHandler.h"
#include "../packets/parsers/ConnAckPacketParser.h"
#include "./mode/CLIMode.h"
#include "mode/ConnectModeHandler.h"
#include "ClientConnectionManager.h"



static void createSessionDirectories(){
    const char* targetDir = "/.lmqtt/client/sessions";
    char* home = getenv("HOME");
    char* dir = (char*) malloc(strlen(home) + strlen(targetDir) + 1);
    strcpy(dir, home);
    strcat(dir,"/.lmqtt");
    Utils::createDirectory(dir);
    strcat(dir,"/client");
    Utils::createDirectory(dir);
    strcat(dir,"/sessions");
    Utils::createDirectory(dir);
}





int main(int argc, char *argv[]) {
    createSessionDirectories();
    // PARSERS
    std::map<PacketType, PacketParser *> parsers;
    ConnAckPacketParser *connAckPacketParser = new ConnAckPacketParser;
    parsers.insert(std::make_pair(CONNACK, connAckPacketParser));

    // FACTORIES
    ConnectPacketFactory* connectPacketFactory = new ConnectPacketFactory();

    FileDataManager* fileDataManager = new FileDataManager();
    ClientConnection* connection = new ClientConnection();
    ClientSessionRepository* clientSessionRepository = new ClientSessionRepository(fileDataManager);

    // gets initialized by attemptConnection
    PacketIOManager *packetIoManager = new PacketIOManager();

    // HANDLERS
    std::map<PacketType, PacketHandler *> handlers;
    ConnectAckPacketHandler* connectAckPacketHandler = new ConnectAckPacketHandler(packetIoManager, clientSessionRepository, connection);
    handlers.insert(std::make_pair(CONNACK, connectAckPacketHandler));

    // CONNECTION PROCESS ENCAPSULATED
    ClientConnectionManager* clientConnectionManager = new ClientConnectionManager(packetIoManager,connectAckPacketHandler,connection, &parsers);

    // MODE HANDLERS
    ConnectModeHandler* connectModeHandler = new ConnectModeHandler(argv, clientConnectionManager,connectPacketFactory,argc);

    CLIMode mode = CLIModes::findCliMode(argv[1]);
    optind = 2;


    switch (mode) {
        case CONNECT_MODE:
            connectModeHandler->handle();
            break;
        case SUBSCRIBE_MODE:
            break;
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