//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTPACKETHANDLER_H
#include "PacketHandler.h"
#include "../packets/ConnectPacket.h"
#include "../con/ConnectionSession.h"
#include "../packets/factories/ConnectAckPacketFactory.h"

class ConnectPacketHandler : public PacketHandler/*<ConnectPacket>*/{
private:
ConnectAckPacketFactory* _connectAckPacketFactory;

public:
    ConnectPacketHandler(ConnectionSession *connectionSession, PacketIOManager *packetIo,ConnectAckPacketFactory* connectAckPacketFactory);
    void handle(RawPacket *rawPacket);
    void connAck(int errorCode, unsigned char cleanSessionFlag);

    ConnectAckPacketFactory *getConnectAckPacketFactory() const;
};
#endif //LMQTT__SERVER_CONNECTPACKETHANDLER_H
