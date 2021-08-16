#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <DisconnectPacketParser.h>
#include <SubscribePacketParser.h>
#include <SubAckPacketFactory.h>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "handlers/PacketHandler.h"
#include "con/ServerConnection.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"
#include "ConnectionManager.h"
#include "topic/TopicRepository.h"


#define PORT 8080



int main(int argc, char const *argv[])
{
    FileDataManager* fileDataManager = new FileDataManager();
    // THESE OBJECTS LIVE AS LONG AS THE SERVER
    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnectPacketParser* connectPacketParser = new ConnectPacketParser;
    DisconnectPacketParser* disconnectPacketParser = new DisconnectPacketParser;
    SubscribePacketParser* subscribePacketParser = new SubscribePacketParser;
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));
    parsers.insert(std::make_pair(DISCONNECT, disconnectPacketParser));
    parsers.insert(std::make_pair(SUBSCRIBE, subscribePacketParser));

    // FACTORIES
    std::map<PacketType,PacketFactory*> factories;
    ConnectAckPacketFactory* connectAckPacketFactory = new ConnectAckPacketFactory();
    factories.insert(std::make_pair(CONNACK, connectAckPacketFactory));
    SubAckPacketFactory* subAckPacketFactory = new SubAckPacketFactory();
    factories.insert(std::make_pair(SUBSCRIBE_ACK, subAckPacketFactory));

    TopicRepository* topicRepository = new TopicRepository(fileDataManager);

    // CREATE DUMMY DATA
    char* testTopic = "jeffseid";
    char* testMessage = "jeff seid trains biceps in mecca";
    topicRepository->store(testTopic, testMessage);


    ConnectionManager* connectionManager = new ConnectionManager(PORT, &parsers, &factories, fileDataManager);
    connectionManager->serveClients();

}


