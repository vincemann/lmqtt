//
// Created by archdoc on 11/09/2021.
//

#include <ServersClientInfoRepository.h>
#include "UnsubscribeCLIModeHandler.h"
#include "CLIMode.h"



void UnsubscribeCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char* topic = 0;
    unsigned char qos = 0xff;
    unsigned char cleanSession = 0;
    // i = clientId, u = username, p = _password, r=removeSession
    //todo learn to make args obsolete (i is needed, i think it was '!' or smth)
    while ((opt = getopt(_argc, _argv, "t:i:")) != -1) {
        switch (opt) {
            case 't': topic = optarg; break;
            case 'i': clientId = optarg; break;
            default: /* '?' */
            CLIModes::printUsageInformation(_argv[0],UNSUBSCRIBE_MODE);
            exit(1);
        }
    }
    initRoute();
    if (clientId == 0){
        fprintf(stderr, "Client Id missing");
        CLIModes::printUsageInformation(_argv[0],UNSUBSCRIBE_MODE);
        exit(1);
    }

    if (topic == 0){
        fprintf(stderr, "Topic is missing");
        CLIModes::printUsageInformation(_argv[0],UNSUBSCRIBE_MODE);
        exit(1);
    }

    ClientsClientInfo* clientsClientInfo = clientsClientInfoRepository->load(clientId);
    if (clientsClientInfo == 0 ){
        printf("You have to call connect to init session before calling subscribe");
        exit(1);
    }
    RawPacket *connectPacket = _connectPacketFactory->create(cleanSession, clientId, clientsClientInfo->_username, clientsClientInfo->_password);
    _clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        _clientConnectionManager->attemptConnection(connectPacket);
        srand(time(NULL));   // Initialization, should only be called once.
        unsigned short packetId = (unsigned short) rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
        printf("packet id:%d\n",packetId);
        UnsubscribePacket* unsubscribePacket = unsubscribePacketFactory->create(packetId,topic);
        _clientConnectionManager->_packetIoManager->sendPacket(unsubscribePacket);
        // wait for unsuback
        RawPacket* unsubackPacket = _clientConnectionManager->_packetIoManager->readPacket();
        unsubAckPacketHandler->handle(unsubackPacket);
        _clientConnectionManager->closeConnection();
        exit(0);
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
//    CLIModeHandler::handle();
}

UnsubscribeCLIModeHandler::UnsubscribeCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                                                     ConnectPacketFactory *connectPacketFactory, int argc,
                                                     ClientsClientInfoRepository *clientsClientInfoRepository,
                                                     UnsubscribePacketFactory *unsubscribePacketFactory,
                                                     UnsubAckPacketHandler *unsubAckPacketHandler) : CLIModeHandler(
        argv, clientConnectionManager, connectPacketFactory, argc), clientsClientInfoRepository(
        clientsClientInfoRepository), unsubscribePacketFactory(unsubscribePacketFactory), unsubAckPacketHandler(
        unsubAckPacketHandler) {}



