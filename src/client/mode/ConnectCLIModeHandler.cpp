//
// Created by vince on 25.07.21.
//

#include <PacketType.h>
#include <cstdlib>
#include <RawPacket.h>
#include <getopt.h>
#include <iostream>
#include <DisconnectPacket.h>
#include "CLIMode.h"
#include "ConnectCLIModeHandler.h"
#include "../../ClientRetransmitMsgHandler.h"


void ConnectCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char *username = 0;
    char *password = 0;
    unsigned char cleanSession = 0;
    unsigned char consume = 0;

    //
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
            {"id", required_argument, 0, 0},
            {"user", required_argument, 0, 0},
            {"password", required_argument, 0, 0},
            {"clean-session", no_argument, 0, 0},
            {"consume-messages", no_argument, 0, 0},
            {0, 0,0, 0}
    };


    while ((opt = getopt_long(_argc, _argv, "", long_options, &option_index)) != -1) {
        switch (opt) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");


                if (strcmp(long_options[option_index].name, "id") == 0) {
                     clientId = optarg;
                } else if (strcmp(long_options[option_index].name, "user") == 0) {
                    username = optarg;
                }else if (strcmp(long_options[option_index].name, "password") == 0) {
                    password = optarg;
                }else if (strcmp(long_options[option_index].name, "clean-session") == 0) {
                    cleanSession = 1;
                }
                else if (strcmp(long_options[option_index].name, "consume-messages") == 0) {
                    consume = 1;
                } else{
                    CLIModes::printUsageInformation(_argv[0], CONNECT_MODE);
                    exit(1);
                }
        }
    }


//    while ((opt = getopt(_argc, _argv, "u:p:i:rm")) != -1) {
//        switch (opt) {
//            case 'u':
//                username = optarg;
//                break;
//            case 'p':
//                password = optarg;
//                break;
//            case 'i':
//                clientId = optarg;
//                break;
//            case 'r':
//                cleanSession = 1;
//                break;
//            case 'm':
//                consume = 1;
//                break;
//            default: /* '?' */
//                CLIModes::printUsageInformation(_argv[0], CONNECT_MODE);
//                exit(1);
//        }
//    }
    initRoute();
    if (clientId == 0) {
        fprintf(stderr, "Client Id missing");
        CLIModes::printUsageInformation(_argv[0], CONNECT_MODE);
        exit(1);
    }
    RawPacket *connectPacket = _connectPacketFactory->create(cleanSession, clientId, username, password, consume);
    clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        clientConnectionManager->attemptConnection(connectPacket);
        clientRetransmitMsgHandler->getClientQosTopicRepository()->initTopicsDir(clientId);
        clientRetransmitMsgHandler->retransmitMsgs();
        if (consume) {
            // wait for publish packets & disconnect packet from server
            clientConnectionManager->handleIncomingPackets();
        } else {
            clientConnectionManager->closeConnection();
            exit(0);
        }
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
}

ConnectCLIModeHandler::ConnectCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                                             ConnectPacketFactory *connectPacketFactory, int argc,
                                             ClientRetransmitMsgHandler *clientRetransmitMsgHandler) : CLIModeHandler(
        argv, clientConnectionManager, connectPacketFactory, argc), clientRetransmitMsgHandler(
        clientRetransmitMsgHandler) {}






