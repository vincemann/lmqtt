//
// Created by vince on 14.07.21.
//

#ifndef LMQTT__SERVER_CONNECTIONMANAGER_H
#define LMQTT__SERVER_CONNECTIONMANAGER_H


#include <FileDataManager.h>

class ConnectionManager {
public:
    ConnectionManager(int port, std::map<PacketType, PacketParser *> *parsers,
                      std::map<PacketType, PacketFactory *> *factories, FileDataManager *pManager);

    void serveClients();
    void disconnectClient();


private:
    int waitForConnection(int serverFd);
    int bindToPort();
    FileDataManager *fileDataManager;
    int _port;
    unsigned char _clientConnected;
    std::map<PacketType,PacketParser*>* _parsers;
    std::map<PacketType,PacketFactory*>* _factories;
};


#endif //LMQTT__SERVER_CONNECTIONMANAGER_H
