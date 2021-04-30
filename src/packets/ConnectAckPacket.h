//
// Created by vince on 30.04.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKET_H
#define LMQTT__SERVER_CONNECTACKPACKET_H
#include "RawPacket.h"


class ConnectAckPacket : public RawPacket {
public:
    ConnectAckPacket(RawPacket *rawPacket, unsigned char sessionPresent, unsigned char returnCode);

    unsigned char getSessionPresent() const;

    unsigned char getReturnCode() const;

private:

    unsigned char _sessionPresent;
    unsigned char _returnCode;
};


#endif //LMQTT__SERVER_CONNECTACKPACKET_H
