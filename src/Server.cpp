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
#include <PublishPacketParser.h>

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
    // THESE OBJECTS LIVE AS LONG AS THE SERVER
    FileDataManager* fileDataManager = new FileDataManager();
    TopicRepository* topicRepository = new TopicRepository(fileDataManager);
    ServerSessionRepository* serverSessionRepository = new ServerSessionRepository(fileDataManager);

    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnectPacketParser* connectPacketParser = new ConnectPacketParser;
    DisconnectPacketParser* disconnectPacketParser = new DisconnectPacketParser;
    SubscribePacketParser* subscribePacketParser = new SubscribePacketParser;
    PublishPacketParser* publishPacketParser = new PublishPacketParser;
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));
    parsers.insert(std::make_pair(DISCONNECT, disconnectPacketParser));
    parsers.insert(std::make_pair(SUBSCRIBE, subscribePacketParser));
    parsers.insert(std::make_pair(PUBLISH, publishPacketParser));

    // FACTORIES
    std::map<PacketType,PacketFactory*> factories;
    ConnectAckPacketFactory* connectAckPacketFactory = new ConnectAckPacketFactory();
    factories.insert(std::make_pair(CONNACK, connectAckPacketFactory));
    SubAckPacketFactory* subAckPacketFactory = new SubAckPacketFactory();
    factories.insert(std::make_pair(SUBSCRIBE_ACK, subAckPacketFactory));

//    TopicRepository* topicRepository = new TopicRepository(fileDataManager);

    // CREATE DUMMY DATA
    char* testTopic = "jeffseid";
    char* testMessage = "jeff seid trains biceps in mecca";
//    char* testMessage2 = "jeff seid trains biceps in mecca2";
//    char* testMessage3 = "jeff seid trains biceps in mecca3";
    topicRepository->store(testTopic, testMessage);
//    topicRepository->store(testTopic, testMessage2);
//    topicRepository->store(testTopic, testMessage3);
//
//    std::vector<Message *>* msgs = topicRepository->loadMessages(testTopic);
//
//    topicRepository->subscribe(testTopic);
//    topicRepository->subscribe(testTopic);
//
//    std::vector<Message *>* msgsAfterSub = topicRepository->loadMessages(testTopic);
//
//
//    std::vector<Message *>* consumedMsgs = topicRepository->consumeMessagesStartingFromId(testTopic,1);
//    std::vector<Message *>* consumedMsgs2 = topicRepository->consumeMessagesStartingFromId(testTopic,1);
//
////    topicRepository->unsubscribe(testTopic,1);
////    topicRepository->unsubscribe(testTopic,1);
//
////    char* testMessage3 = "test msg2";
////    char* testMessage4 = "test msg3";
////    Message* tmsg3 = new Message(2,1,testMessage3);
////    Message* tmsg4 = new Message(3,1, testMessage4);
////    msgs = new std::vector<Message*>();
////    msgs->push_back(tmsg3);
////    msgs->push_back(tmsg4);
////    topicRepository->replaceMessages(testTopic, msgs);


    ConnectionManager* connectionManager = new ConnectionManager(PORT, &parsers, &factories,
                                                                 topicRepository, serverSessionRepository);
    connectionManager->serveClients();

}


