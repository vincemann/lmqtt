//
// Created by vince on 12.08.21.
//

#include <SubscribeAckPacket.h>
#include <SubscribePacket.h>
#include <InvalidPacketException.h>
#include "SubscribeAckPacketHandler.h"

SubscribeAckPacketHandler::SubscribeAckPacketHandler(PacketIOManager *packetIo, ClientConnection *clientConnection)
        : PacketHandler(packetIo), clientConnection(clientConnection) {}

void SubscribeAckPacketHandler::handle(RawPacket *packet) {
    SubscribeAckPacket* subAckPacket = static_cast<SubscribeAckPacket*>(packet);
    unsigned char retCode = subAckPacket->getRetCode();
    if (retCode >= 0 && retCode <3 ){
        printf("Subscribe packet acked successfully with qos: %d\n",retCode);
    } else{
        printf("Subscribe packet acked error code: %d\n",retCode);
    }

    SubscribePacket* subscribePacket = static_cast<SubscribePacket*>(clientConnection->_packetsSent->back());
    printf("subscribe packet id: %d\n", subscribePacket->getPacketId());
    printf("subscribe ack packet id: %d\n", subAckPacket->getPacketId());


    if (subscribePacket->getPacketId() != subAckPacket->getPacketId()){
        throw InvalidPacketException("Invalid packet Id");
    }

}
