//
// Created by vince on 07.04.21.
//

#include <unistd.h>

#include "PacketSender.h"
#include "../packets/RawPacket.h"
#include "PacketParsingException.h"


static void err(const char* msg){
    throw new PacketParsingException(msg);
}

static unsigned char eval_packet_type_bits(PacketType packetType){
    switch (packetType) {
        case CONNECT:
            return 1;
    }
    err("unknown packet type");
}

void PacketSender::send(const RawPacket &packet) {

    // send first fixed header byte
    unsigned char control_fixed_header [] = { packet.getSpecificFlags() & eval_packet_type_bits(packet.getType()) };
    if (write(_socket_fd,&control_fixed_header,1) != 1){
        err("cant send control_fixed_header");
    }
    // send length
    unsigned char len = packet.getLength();
    unsigned char length_fixed_header [] = { len };
    if (write(_socket_fd,&length_fixed_header,1) != 1){
        err("cant send length_fixed_header");
    }
    // send data
    if (write(_socket_fd,packet.getData(),packet.getLength()) != packet.getLength()){
        err("cant send packet data");
    }

}

PacketSender::PacketSender(int socketFd) : _socket_fd(socketFd) {}
