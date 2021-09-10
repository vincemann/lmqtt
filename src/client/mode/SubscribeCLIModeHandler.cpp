//
// Created by vince on 27.07.21.
//

#include "SubscribeCLIModeHandler.h"
#include "CLIMode.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void SubscribeCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char* topic = 0;
    unsigned char qos = 0xff;
    unsigned char cleanSession = 0;
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
    initRoute();
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


    ClientsClientInfo* clientSession = clientSessionRepository->load(clientId);
    if (clientSession == 0 ){
        printf("You have to call connect to init session before calling subscribe");
        exit(1);
    }


    RawPacket *connectPacket = _connectPacketFactory->create(cleanSession, clientId, clientSession->_username, clientSession->_password);
    _clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        _clientConnectionManager->attemptConnection(connectPacket);
        std::cout << "Successfully _connected to Server!" << "\n";
        srand(time(NULL));   // Initialization, should only be called once.
        unsigned short packetId = (unsigned short) rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
        printf("packet id:%d\n",packetId);
        SubscribePacket* subscribePacket = subscribePacketFactory->create(packetId,topic,qos);
        _clientConnectionManager->_packetIoManager->sendPacket(subscribePacket);
        // wait for suback
        RawPacket* subackPacket = _clientConnectionManager->_packetIoManager->readPacket();
        subscribeAckPacketHandler->handle(subackPacket);
        _clientConnectionManager->closeConnection();
        exit(0);
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
}

SubscribeCLIModeHandler::SubscribeCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                                                 ConnectPacketFactory *connectPacketFactory, int argc,
                                                 ClientsClientInfoRepository *clientSessionRepository,
                                                 SubscribePacketFactory *subscribePacketFactory, SubscribeAckPacketHandler* subscribeAckPacketHandler) : CLIModeHandler(
        argv, clientConnectionManager, connectPacketFactory, argc), clientSessionRepository(clientSessionRepository),
        subscribePacketFactory(subscribePacketFactory), subscribeAckPacketHandler(subscribeAckPacketHandler) {}
