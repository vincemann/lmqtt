//
// Created by vince on 25.07.21.
//

#include <PacketParser.h>
#include <PacketIOManager.h>
#include <ConnectAckPacketHandler.h>
#include <unistd.h>
#include "ModeHandler.h"


void ModeHandler::initRoute(){
    _clientConnectionManager->setIp(_argv[optind]);
    _clientConnectionManager->setPort(strtol(_argv[optind+1],nullptr,10));
    printf("route: %s:%d\n",_clientConnectionManager->_ip,_clientConnectionManager->_port);
}


ModeHandler::ModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                         ConnectPacketFactory *connectPacketFactory, int argc) : _argv(argv),
                                                                                 _clientConnectionManager(
                                                                                                  clientConnectionManager),
                                                                                 _connectPacketFactory(connectPacketFactory),
                                                                                 _argc(argc) {}

void ModeHandler::handle() {

}

ModeHandler::~ModeHandler() {

}


