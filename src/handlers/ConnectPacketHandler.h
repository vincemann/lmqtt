//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../con/ConnectionSession.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "../FileLocator.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
private:
ConnectAckPacketFactory* _connectAckPacketFactory;
FileLocator* _fileLocator;
protected:
Session* findSession(char* clientId);
Session* createSession(unsigned char cleanSession, char* clientId);
public:
    ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory* connectAckPacketFactory, FileLocator* fileLocator);
    void handle(RawPacket *rawPacket);
    void connAck(int errorCode, unsigned char cleanSessionFlag);

    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
