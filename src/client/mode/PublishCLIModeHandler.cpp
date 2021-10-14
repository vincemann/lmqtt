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
    char *topic = 0;
    unsigned char qos = 0xff;
    // i = clientId, u = username, p = _password, r=removeSession
    //todo learn to make args obsolete (i is needed, i think it was '!' or smth)
    while ((opt = getopt(_argc, _argv, "t:i:q:")) != -1) {
        switch (opt) {
            case 't':
                topic = optarg;
                break;
            case 'i':
                clientId = optarg;
                break;
            case 'q':
                qos = atoi(optarg);
                break;
            default: /* '?' */
                CLIModes::printUsageInformation(_argv[0], PUBLISH_MODE);
                exit(1);
        }
    }

    if (clientId == 0) {
        fprintf(stderr, "Client Id missing");
        CLIModes::printUsageInformation(_argv[0], PUBLISH_MODE);
        exit(1);
    }

    if (topic == 0) {
        fprintf(stderr, "Topic is missing");
        CLIModes::printUsageInformation(_argv[0], PUBLISH_MODE);
        exit(1);
    }
    if (qos == 0xff) {
        fprintf(stderr, "Qos is missing");
        CLIModes::printUsageInformation(_argv[0], PUBLISH_MODE);
        exit(1);
    }


    ClientsClientInfo *clientSession = clientSessionRepository->load(clientId);
    if (clientSession == 0) {
        printf("You have to call connect to init session before calling subscribe");
        exit(1);
    }

    char *msg = _argv[optind++];
    initRoute();
    clientRetransmitMsgHandler->getClientQosTopicRepository()->initTopicsDir(clientId);
    RawPacket *connectPacket = _connectPacketFactory->create(0, clientId, clientSession->_username,
                                                             clientSession->_password, 0);
    clientConnectionManager->_connection->_connectPacket = static_cast<ConnectPacket *>(connectPacket);
    try {
        clientConnectionManager->attemptConnection(connectPacket);
        PublishPacket *publishPacket = publishPacketFactory->create(qos, 0, topic, msg, 0);
        clientConnectionManager->packetIoManager->sendPacket(publishPacket);

        if (qos == 0) {
            printf("Closing Connection\n");
            clientConnectionManager->closeConnection();
        } else if (qos ==1){
            clientRetransmitMsgHandler->saveMsg(new ClientQosMessageContainer(publishPacket));
            // wait for puback
            RawPacket* pubResponsePackage = clientConnectionManager->packetIoManager->readPacket();
            clientPublishAckPacketHandler->handle(pubResponsePackage);
            clientConnectionManager->closeConnection();
        } else{
            printf("invalid qos\n");
        }
        exit(0);
    } catch (const std::exception &e) {
        std::cout << "exception occurred while creating _connection with server:" << "\n";
        std::cout << e.what() << "\n";
        exit(1);
    }
}

PublishCLIModeHandler::PublishCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                                             ConnectPacketFactory *connectPacketFactory, int argc,
                                             ClientsClientInfoRepository *clientSessionRepository,
                                             PublishPacketFactory *publishPacketFactory,
                                             ClientPublishAckPacketHandler *clientPublishAckPacketHandler,ClientRetransmitMsgHandler* clientRetransmitMsgHandler)
        : CLIModeHandler(argv,
                         clientConnectionManager,
                         connectPacketFactory,
                         argc),
          clientSessionRepository(
                  clientSessionRepository),
          publishPacketFactory(
                  publishPacketFactory),
          clientPublishAckPacketHandler(clientPublishAckPacketHandler), clientRetransmitMsgHandler(clientRetransmitMsgHandler) {}





