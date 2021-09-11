//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_CONNECTIONMANAGER_H
#define LMQTT__SERVER_CONNECTIONMANAGER_H


#include <FileDataManager.h>
#include <ServerSessionRepository.h>
#include "topic/TopicRepository.h"

class ConnectionManager {
public:
    ConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                      std::map<PacketType, PacketFactory *> *factories,
                      TopicRepository *topicRepository,
                      ServerSessionRepository *serverSessionRepository);

    void serveClients();
    void disconnectClient();


private:
    int waitForConnection(int serverFd);
    int bindToPort();
    ServerSessionRepository* serverSessionRepository;
    TopicRepository* topicRepository;
    int _port;
    unsigned char _clientConnected;
    std::map<PacketType,PacketParser*>* _parsers;
    std::map<PacketType,PacketFactory*>* _factories;
};


#endif //LMQTT__SERVER_CONNECTIONMANAGER_H
