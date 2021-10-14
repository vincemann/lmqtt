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
#include <getopt.h>
#include <PublishAckPacketParser.h>


#define PORT 8080

int NO_PUB_ACK_COUNT = 0;
int NO_PUB_ACK_COUNT_START = 0;


static void set_test_flags(int argc, char *argv[]) {
    int opt;

    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
            {"no-publish-ack-count", required_argument, 0, 0},
            {"no-publish-ack-start", required_argument, 0, 0},
//            {"delete",  required_argument, 0,  0 },
//            {"verbose", no_argument,       0,  0 },
//            {"create",  required_argument, 0, 'c'},
//            {"file",    required_argument, 0,  0 },
            {0, 0,                                      0, 0}
    };


    while ((opt = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {
        switch (opt) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");


                if (strcmp(long_options[option_index].name, "no-publish-ack-count") == 0) {
                    NO_PUB_ACK_COUNT = strtol(optarg, 0, 10);
                } else if (strcmp(long_options[option_index].name, "no-publish-ack-start") == 0) {
                    NO_PUB_ACK_COUNT_START = strtol(optarg, 0, 10);
                }
        }
    }
}


int main(int argc, char *argv[]) {
    set_test_flags(argc, argv);
    // THESE OBJECTS LIVE AS LONG AS THE SERVER
    FileDataManager *fileDataManager = new FileDataManager();
    ServersClientInfoRepository *serversClientInfoRepository = new ServersClientInfoRepository(fileDataManager);
    // nullpointer is legit, will be set later
    ServerTopicRepository *topicRepository = new ServerTopicRepository(fileDataManager, serversClientInfoRepository,
                                                                       0);

    // PARSERS
    std::map<PacketType, PacketParser *> parsers;
    ConnectPacketParser *connectPacketParser = new ConnectPacketParser;
    DisconnectPacketParser *disconnectPacketParser = new DisconnectPacketParser;
    SubscribePacketParser *subscribePacketParser = new SubscribePacketParser;

    PublishPacketParser *publishPacketParser = new PublishPacketParser;
    UnsubscribePacketParser *unsubscribePacketParser = new UnsubscribePacketParser;
    UnsubAckPacketParser *unsubAckPacketParser = new UnsubAckPacketParser;
    PublishAckPacketParser* publishAckPacketParser = new PublishAckPacketParser();
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));
    parsers.insert(std::make_pair(DISCONNECT, disconnectPacketParser));
    parsers.insert(std::make_pair(SUBSCRIBE, subscribePacketParser));
    parsers.insert(std::make_pair(PUBLISH, publishPacketParser));
    parsers.insert(std::make_pair(PUBLISH_ACK, publishAckPacketParser));
    parsers.insert(std::make_pair(UNSUBSCRIBE, unsubscribePacketParser));
    parsers.insert(std::make_pair(UNSUB_ACK, unsubAckPacketParser));

    // FACTORIES
    std::map<PacketType, PacketFactory *> factories;
    ConnectAckPacketFactory *connectAckPacketFactory = new ConnectAckPacketFactory();
    factories.insert(std::make_pair(CONNECT_ACK, connectAckPacketFactory));
    SubAckPacketFactory *subAckPacketFactory = new SubAckPacketFactory();
    factories.insert(std::make_pair(SUBSCRIBE_ACK, subAckPacketFactory));
    UnsubscribePacketFactory *unsubscribePacketFactory = new UnsubscribePacketFactory();
    factories.insert(std::make_pair(UNSUBSCRIBE, unsubscribePacketFactory));
    UnsubAckPacketFactory *unsubAckPacketFactory = new UnsubAckPacketFactory();
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



    ServerConnectionManager *connectionManager = new ServerConnectionManager(PORT, &parsers, &factories,
                                                                             topicRepository,
                                                                             serversClientInfoRepository);
    connectionManager->serveClients();
}


