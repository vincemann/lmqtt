//
// Created by archdoc on 10/09/2021.
//

#include <UnsubAckPacket.h>
#include "UnsubAckPacketHandler.h"


UnsubAckPacketHandler::UnsubAckPacketHandler(PacketIOManager *packetIo): PacketHandler(packetIo) {}

void UnsubAckPacketHandler::handle(RawPacket *rawPacket) {
    auto *packet = static_cast<UnsubAckPacket *>(rawPacket);
//    unsub_ack packetId is the same as the unsub package that is being acknowledged
    printf("Received unsub_ack package %d\n", packet->getPacketId());
}
