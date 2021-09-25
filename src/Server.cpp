#include <DisconnectPacketParser.h>
#include <SubscribePacketParser.h>
#include <SubAckPacketFactory.h>
#include <UnsubscribePacketParser.h>
#include <UnsubAckPacketParser.h>
#include <UnsubscribePacketFactory.h>
#include <UnsubAckPacketFactory.h>
#include <PublishPacketParser.h>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"
#include "ServerConnectionManager.h"
#include "topic/ServerTopicRepository.h"


#define PORT 8080



int main(int argc, char const *argv[])
{
    // THESE OBJECTS LIVE AS LONG AS THE SERVER
    FileDataManager* fileDataManager = new FileDataManager();
    ServersClientInfoRepository* serversClientInfoRepository = new ServersClientInfoRepository(fileDataManager);
    // nullpointer is legit, will be set later
    ServerTopicRepository* topicRepository = new ServerTopicRepository(fileDataManager, serversClientInfoRepository,
                                                                       nullptr);

    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnectPacketParser* connectPacketParser = new ConnectPacketParser;
    DisconnectPacketParser* disconnectPacketParser = new DisconnectPacketParser;
    SubscribePacketParser* subscribePacketParser = new SubscribePacketParser;

    PublishPacketParser* publishPacketParser = new PublishPacketParser;
    UnsubscribePacketParser* unsubscribePacketParser = new UnsubscribePacketParser;
    UnsubAckPacketParser* unsubAckPacketParser = new UnsubAckPacketParser;
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));
    parsers.insert(std::make_pair(DISCONNECT, disconnectPacketParser));
    parsers.insert(std::make_pair(SUBSCRIBE, subscribePacketParser));
    parsers.insert(std::make_pair(PUBLISH, publishPacketParser));
    parsers.insert(std::make_pair(UNSUBSCRIBE, unsubscribePacketParser));
    parsers.insert(std::make_pair(UNSUB_ACK, unsubAckPacketParser));

    // FACTORIES
    std::map<PacketType,PacketFactory*> factories;
    ConnectAckPacketFactory* connectAckPacketFactory = new ConnectAckPacketFactory();
    factories.insert(std::make_pair(CONNACK, connectAckPacketFactory));
    SubAckPacketFactory* subAckPacketFactory = new SubAckPacketFactory();
    factories.insert(std::make_pair(SUBSCRIBE_ACK, subAckPacketFactory));
    UnsubscribePacketFactory* unsubscribePacketFactory = new UnsubscribePacketFactory();
    factories.insert(std::make_pair(UNSUBSCRIBE, unsubscribePacketFactory));
    UnsubAckPacketFactory* unsubAckPacketFactory = new UnsubAckPacketFactory();
    factories.insert(std::make_pair(UNSUB_ACK, unsubAckPacketFactory));


//    ServerTopicRepository* topicRepository = new ServerTopicRepository(fileDataManager);

// todo write python test
    // CREATE DUMMY DATA
//    char* testTopic = "jeffseid";
//
//    topicRepository->saveTopic(new Topic(testTopic));
//    char* testMessage = "jeff seid trains biceps in mecca";
//    char* testMessage2 = "jeff seid trains biceps in mecca2";
//    char* testMessage3 = "jeff seid trains biceps in mecca3";
//    topicRepository->saveMsg(testTopic, testMessage);
//    topicRepository->saveMsg(testTopic, testMessage2);
//    topicRepository->saveMsg(testTopic, testMessage3);
//
//    std::vector<ServerMessageContainer *>* msgs = topicRepository->loadMessages(testTopic);
//
//    topicRepository->subscribe(testTopic,0);
//    topicRepository->subscribe(testTopic,0);
//
//    std::vector<ServerMessageContainer* *>* msgsAfterSub = topicRepository->loadMessages(testTopic);
//
//
//    std::vector<ServerMessageContainer *>* consumedMsgs = topicRepository->consumeMessagesStartingFromId(testTopic,1);
//    std::vector<ServerMessageContainer *>* consumedMsgs2 = topicRepository->consumeMessagesStartingFromId(testTopic,1);

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



    ServerConnectionManager* connectionManager = new ServerConnectionManager(PORT, &parsers, &factories,
                                                                             topicRepository, serversClientInfoRepository);
    connectionManager->serveClients();
}


