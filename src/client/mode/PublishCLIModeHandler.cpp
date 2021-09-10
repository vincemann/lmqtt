//
// Created by vince on 10.09.21.
//

#include "PublishCLIModeHandler.h"

#include "CLIMode.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <PublishPacket.h>

void PublishCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char* topic = 0;
    unsigned char qos = 0xff;
    // i = clientId, u = username, p = _password, r=removeSession
    //todo learn to make args obsolete (i is needed, i think it was '!' or smth)
    while ((opt = getopt(_argc, _argv, "t:i:q:")) != -1) {
        switch (opt) {
            case 't': topic = optarg; break;
            case 'i': clientId = optarg; break;
            case 'q': qos = atoi(optarg); break;
            default: /* '?' */
                CLIModes::printUsageInformation(_argv[0],SUBSCRIBE);
                exit(1);
        }
    }

    if (clientId == 0){
        fprintf(stderr, "Client Id missing");
        CLIModes::printUsageInformation(_argv[0],SUBSCRIBE);
        exit(1);
    }

    if (topic == 0){
        fprintf(stderr, "Topic is missing");
        CLIModes::printUsageInformation(_argv[0],SUBSCRIBE);
        exit(1);
    }
    if (qos == 0xff){
        fprintf(stderr, "Qos is missing");
        CLIModes::printUsageInformation(_argv[0],SUBSCRIBE);
        exit(1);
    }


    ClientSession* clientSession = clientSessionRepository->load(clientId);
    if (clientSession == 0 ){
        printf("You have to call connect to init session before calling subscribe");
        exit(1);
    }

    char* msg = _argv[optind++];
    initRoute();

    RawPacket *connectPacket = _connectPacketFactory->create(0, clientId, clientSession->_username, clientSession->_password);
    _clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        _clientConnectionManager->attemptConnection(connectPacket);
        std::cout << "Successfully _connected to Server!" << "\n";
        PublishPacket* publishPacket = publishPacketFactory->create(qos, 0,topic,msg,0);
        _clientConnectionManager->_packetIoManager->sendPacket(publishPacket);
        // wait for puback
//        RawPacket* pubAckPackage = _clientConnectionManager->_packetIoManager->readPacket();
//        subscribeAckPacketHandler->handle(subackPacket);
        _clientConnectionManager->closeConnection();
        exit(0);
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
}

