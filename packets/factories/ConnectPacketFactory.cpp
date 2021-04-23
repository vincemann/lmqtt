//
// Created by vince on 23.04.21.
//

#include "ConnectPacketFactory.h"
#include "../../packets/ConnectPacket.h"
#include "../../packets/RawPacket.h.h"
#include "../../packets/PacketType.h"

// give me ConnectPacket with raw packet null and i will gen raw packet ready to send
RawPacket *ConnectPacketFactory::create(RawPacket *raw_packet) {
    ConnectPacket* connectPacket = dynamic_cast<ConnectPacket*>(raw_packet);
    RawPacket resultPacket = new RawPacket();
    // IO Manager puts this into packet for me
    resultPacket.setType(CONNECT);
    resultPacket.setSpecificFlags(0);

    char* protocolName = PacketFactory::createUtf8Payload("MQTT");
    char protocolLevel = 4;


    return NULL;
}
