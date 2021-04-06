//
// Created by vince on 06.04.21.
//

#include "PacketParser.h"

#include <unistd.h>
#include "Parser"
#include "ParserException.h"
#include "../PacketType.h"
#include <map>
#include "../packet_factories/ConnectPacketFactory.h"


unsigned create_mask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}


void err(const char* msg){
    throw new ParserException(msg)
}


PacketType eval_packet_type( unsigned char fixed_header_buf[]){
    unsigned char mask = create_mask(4,7);
    unsigned char packet_type_val = mask & fixed_header_buf[0];
    switch (packet_type_val) {
        case 1:
            return PacketType::CONNECT;
    }
    err("unknown packet type");
}

void eval_specific_flags(bool[4] result, unsigned char fixed_header_buf[]){
    unsigned char mask = create_mask(0,3);
    unsigned char specific_flags_val = mask & fixed_header_buf[0];
    for (int i =0; i < 4;i++){
        bool bit = (specific_flags_val >> i) & 1;
        result[i] = bit;
    }
}

unsigned int eval_length(int socket_fd){
    // for now just support small sizes
    unsigned char length_fixed_header_buf = [1];
    if(read(socket_fd, control_fixed_header_buf, 1) != 1){
        err("Cant read length fixed header");
    }
    return length_fixed_header_buf[0];
}


PacketParser::PacketParser(std::map<PacketType,ConnectPacketFactory*> & factories) {
   this->_packet_factories=factories
}

template<class P>
P PacketParser::read_next(int socket_fd) {
    // read fixed header
    unsigned char control_fixed_header_buf = [1];
    if(read(socket_fd, control_fixed_header_buf, 1) != 1){
        err("Cant read mqtt control fixed header");
    }

    bool[4] specific_flags;
    eval_specific_flags(specific_flags,specific_flags_val);
    PacketType packet_type = eval_packet_type(packet_type_val);
    int length = eval_length(socket_fd);

    unsigned char data_buf[length];
    if(read(socket_fd, data_buf, length) != length){
        err("Cant read packet data");
    }
    

    RawPacket* rawPacket = new RawPacket(packet_type,specific_flags,length,data_buf);
    ConnectPacketFactory *factory  = _packet_factories[packet_type];
    ConnectPacket* connect_packet = factory->create(rawPacket);
    return dynamic_cast<P>(connect_packet);
}





