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


void ConnectCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char *username = 0;
    char *password = 0;
    unsigned char cleanSession = 0;
    unsigned char consume = 0;
    // i = clientId, u = username, p = _password, r=removeSession
    //todo learn to make args obsolete (i is needed, i think it was '!' or smth)
    while ((opt = getopt(_argc, _argv, "u:p:i:rm")) != -1) {
        switch (opt) {
            case 'u':
                username = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            case 'i':
                clientId = optarg;
                break;
            case 'r':
                cleanSession = 1;
                break;
            case 'm':
                consume = 1;
                break;
            default: /* '?' */
                CLIModes::printUsageInformation(_argv[0], CONNECT_MODE);
                exit(1);
        }
    }
    initRoute();
    if (clientId == 0) {
        fprintf(stderr, "Client Id missing");
        CLIModes::printUsageInformation(_argv[0], CONNECT_MODE);
        exit(1);
    }
    RawPacket *connectPacket = _connectPacketFactory->create(cleanSession, clientId, username, password, consume);
    _clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        _clientConnectionManager->attemptConnection(connectPacket);
        // wait for publish packets & disconnect packet from server
        if (consume) {
            _clientConnectionManager->handleIncomingPackets();
        } else {
            _clientConnectionManager->closeConnection();
            exit(0);
        }
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
}

ConnectCLIModeHandler::ConnectCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                                             ConnectPacketFactory *connectPacketFactory, int argc) : CLIModeHandler(
        argv,
        clientConnectionManager,
        connectPacketFactory,
        argc) {

}


