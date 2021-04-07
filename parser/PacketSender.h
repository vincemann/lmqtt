//
// Created by vince on 07.04.21.
//

#ifndef LMQTT__SERVER_PACKETSENDER_H
#define LMQTT__SERVER_PACKETSENDER_H

#include "../packets/RawPacket.h"

class PacketSender {
private:
    int _socket_fd;
public:
    PacketSender(int socketFd);
    void send(const RawPacket &packet);
};


#endif //LMQTT__SERVER_PACKETSENDER_H
