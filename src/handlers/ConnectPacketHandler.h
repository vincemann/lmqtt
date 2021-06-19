//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../con/ConnectionSession.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "../files/FileDataManager.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
protected:
ConnectAckPacketFactory* _connectAckPacketFactory;
FileDataManager* _fileDataManager;
Session* findSession(char* clientId);
Session* createSession(unsigned char cleanSession, char* clientId);
void connAck(int errorCode, unsigned char cleanSessionFlag);


public:
    ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory* connectAckPacketFactory, FileDataManager* fileDataManager);
    void handle(RawPacket *rawPacket);
    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
