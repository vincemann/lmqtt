//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../ConnectionSession.h"
#include "../packets/factories/ConnectAckPacketFactory.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
private:
ConnectAckPacketFactory* _connectAckPacketFactory;

public:
    ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory* connectAckPacketFactory);
    void handle(RawPacket *rawPacket);
    void connAck(int errorCode, const char* msg,unsigned char cleanSessionFlag, bool closeCon=true);
    void closeConnectionWithoutAck(const char* errorMsg);

    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
