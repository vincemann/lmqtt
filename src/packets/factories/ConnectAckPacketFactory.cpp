//
// Created by vince on 30.04.21.
//

#include "ConnectAckPacketFactory.h"
#include "../ConnectAckPacket.h"

ConnectAckPacket *ConnectAckPacketFactory::create(unsigned char returnCode, unsigned char sessionPresent) {
    unsigned char specificFlags = 0;
    unsigned int payloadLen = 2;
    unsigned char *payload = new char[2];
    // first 7 bits must be 0 -> reserved
    if ( (sessionPresent > 1) || (sessionPresent < 0) ){
        throw new PacketCreationException("invalid session present flag");
    }
    payload[0] = sessionPresent;
    if ( (returnCode > 5) || (returnCode < 0) ){
        throw new PacketCreationException("invalid ret code");
    }
    payload[1]= returnCode;
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, CONNACK);
    return new ConnectAckPacket(rawPacket,sessionPresent,returnCode);
}
