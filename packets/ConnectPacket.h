//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKET_H
#define LMQTT__SERVER_CONNECTPACKET_H

#include "RawPacket.h"

class ConnectPacket : public RawPacket{
public:
    ConnectPacket(unsigned int length, char *data);
};

#endif //LMQTT__SERVER_CONNECTPACKET_H
