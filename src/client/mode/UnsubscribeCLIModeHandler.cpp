//
// Created by archdoc on 11/09/2021.
//

#include <ServersClientInfoRepository.h>
#include "UnsubscribeCLIModeHandler.h"
#include "CLIMode.h"
#include <getopt.h>
#include <unistd.h>



void UnsubscribeCLIModeHandler::handle() {
    int opt;

    char *clientId = 0;
    char *topic = 0;

    //
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
            {"id", required_argument, 0, 0},
            {"topic", required_argument, 0, 0},
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
                } else if (strcmp(long_options[option_index].name, "topic") == 0) {
                    topic = optarg;
                } else{
                    CLIModes::printUsageInformation(_argv[0], UNSUBSCRIBE_MODE);
                    exit(1);
                }
        }
    }
//    char *clientId = 0;
//    char* topic = 0;
//    unsigned char qos = 0xff;
//    unsigned char cleanSession = 0;
//    // i = clientId, u = username, p = _password, r=removeSession
//    while ((opt = getopt(_argc, _argv, "t:i:")) != -1) {
//        switch (opt) {
//            case 't': topic = optarg; break;
//            case 'i': clientId = optarg; break;
//            default: /* '?' */
//            CLIModes::printUsageInformation(_argv[0],UNSUBSCRIBE_MODE);
//            exit(1);
//        }
//    }
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
        printf("You have to call connect to init session before calling unsubscribe");
        exit(1);
    }
    RawPacket *connectPacket = _connectPacketFactory->create(0, clientId, clientsClientInfo->_username, clientsClientInfo->_password,0);
    clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        clientConnectionManager->attemptConnection(connectPacket);
        int packetId = Utils::gen_random_packet_id();
        printf("packet id:%d\n",packetId);
        UnsubscribePacket* unsubscribePacket = unsubscribePacketFactory->create(packetId,topic);
        clientConnectionManager->packetIoManager->sendPacket(unsubscribePacket);
        // wait for unsuback
        RawPacket* unsubackPacket = clientConnectionManager->packetIoManager->readPacket();
        unsubAckPacketHandler->handle(unsubackPacket);
        clientConnectionManager->closeConnection();
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



