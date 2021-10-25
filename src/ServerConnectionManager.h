//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_SERVERCONNECTIONMANAGER_H
#define LMQTT__SERVER_SERVERCONNECTIONMANAGER_H


#include <FileDataManager.h>
#include <ServersClientInfoRepository.h>
#include "topic/ServerTopicRepository.h"
#include "ServerQosTopicRepository.h"

class ServerConnectionManager {
public:
    ServerConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                            std::map<PacketType, PacketFactory *> *factories,
                            ServerTopicRepository *topicRepository,
                            ServersClientInfoRepository *serversClientInfoRepository,
                            ServerQosTopicRepository *serverQosTopicRepository);

    void serveClients();
    void disconnectClient();


private:
    int waitForConnection(int serverFd);
    int bindToPort();
    ServersClientInfoRepository* serversClientInfoRepository;
    ServerTopicRepository* topicRepository;
    int _port;
    unsigned char _clientConnected;
    std::map<PacketType,PacketParser*>* _parsers;
    std::map<PacketType,PacketFactory*>* _factories;
    ServerQosTopicRepository* serverQosTopicRepository;
};


#endif //LMQTT__SERVER_SERVERCONNECTIONMANAGER_H
