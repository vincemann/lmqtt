
#include "../ConnectAckPacket.h"
#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"
#include "ConnAckPacketParser.h"

RawPacket* ConnAckPacketParser::parse(RawPacket* packet) 
{
    unsigned char* data = packet->getData();
    unsigned char sessionPresent = data[0];
    unsigned char retCode = data[1];
    ConnectAckPacket *result = new ConnectAckPacket(packet,sessionPresent,retCode);
    return result;
}
