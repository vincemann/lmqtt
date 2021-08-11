//
// Created by vince on 12.08.21.
//

#include <SubAckPacket.h>
#include "SubscribeAckPacketHandler.h"

SubscribeAckPacketHandler::SubscribeAckPacketHandler(PacketIOManager *packetIo) : PacketHandler(packetIo) {}

void SubscribeAckPacketHandler::handle(RawPacket *packet) {
    SubAckPacket* subAckPacket = static_cast<SubAckPacket*>(packet);
    unsigned char retCode = subAckPacket->getRetCode();
    if (retCode >= 0 && retCode <3 ){
        printf("Subscribe packet acked successfully with qos: %d\n",retCode);
    } else{
        printf("Subscribe packet acked error code: %d\n",retCode);
    }
}
