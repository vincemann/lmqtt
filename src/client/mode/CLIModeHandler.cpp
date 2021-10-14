//
// Created by vince on 25.07.21.
//

#include <PacketParser.h>
#include <PacketIOManager.h>
#include <ConnectAckPacketHandler.h>
#include <unistd.h>
#include "CLIModeHandler.h"


void CLIModeHandler::initRoute(){
    clientConnectionManager->setIp(_argv[optind]);
    clientConnectionManager->setPort(strtol(_argv[optind + 1], nullptr, 10));
    printf("route: %s:%d\n", clientConnectionManager->_ip, clientConnectionManager->_port);
}


CLIModeHandler::CLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                               ConnectPacketFactory *connectPacketFactory, int argc) : _argv(argv),
                                                                                       clientConnectionManager(
                                                                                                  clientConnectionManager),
                                                                                       _connectPacketFactory(connectPacketFactory),
                                                                                       _argc(argc) {}

void CLIModeHandler::handle() {

}

CLIModeHandler::~CLIModeHandler() {

}


