#ifndef __CONNACKPACKETPARSER_H__
#define __CONNACKPACKETPARSER_H__

#include "../ConnectPacket.h"
#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"

class ConnAckPacketParser : public PacketParser/*<ConnectPacket>*/{
public:
//    ConnectPacket* parse(RawPacket* pRawPacket);
    RawPacket* parse(RawPacket* pRawPacket);
};
#endif // __CONNACKPACKETPARSER_H__