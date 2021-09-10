//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_CONNECTIONMANAGER_H
#define LMQTT__SERVER_CONNECTIONMANAGER_H


#include <FileDataManager.h>
#include <ServersClientInfoRepository.h>
#include "topic/ServerTopicRepository.h"

class ConnectionManager {
public:
    ConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                      std::map<PacketType, PacketFactory *> *factories,
                      ServerTopicRepository *topicRepository,
                      ServersClientInfoRepository *serverSessionRepository);

    void serveClients();
    void disconnectClient();


private:
    int waitForConnection(int serverFd);
    int bindToPort();
    ServersClientInfoRepository* serverSessionRepository;
    ServerTopicRepository* topicRepository;
    int _port;
    unsigned char _clientConnected;
    std::map<PacketType,PacketParser*>* _parsers;
    std::map<PacketType,PacketFactory*>* _factories;
};


#endif //LMQTT__SERVER_CONNECTIONMANAGER_H
