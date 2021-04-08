//
// Created by vince on 06.04.21.
//



#include <unistd.h>
#include <map>

#include "PacketReceiver.h"
#include "factories/ConnectPacketFactory.h"
#include "PacketParsingException.h"
#include "../packets/PacketType.h"
#include <stdio.h>
#include "../util/Utils.h"


static unsigned create_mask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}


static void err(const char* msg){
    throw new PacketParsingException(msg);
}


static PacketType eval_packet_type( unsigned char fixed_header_byte){
    unsigned char mask = create_mask(4,7);
    unsigned char packet_type_val = Utils::reverse_bits(mask & fixed_header_byte);


    printf("packet type bits:\n");
    Utils::print_bits(packet_type_val);
    printf("packet type resulting number: %d",packet_type_val);


    switch (packet_type_val) {
        case 1:
            return PacketType::CONNECT;
    }
    err("unknown packet _type");
}

static unsigned char eval_specific_flags(/*bool[4] result,*/ unsigned char fixed_header_byte){
    unsigned char mask = create_mask(0,3);
    unsigned char specific_flags = mask & fixed_header_byte;
    return specific_flags;
//    for (int i =0; i < 4;i++){
//        bool bit = (specific_flags >> i) & 1;
//        result[i] = bit;
//    }
}

static unsigned int eval_length(int socket_fd){
    // for now just support small sizes
    unsigned char length_fixed_header_buf[1];
    if(read(socket_fd, length_fixed_header_buf, 1) != 1){
        err("Cant read _length fixed header");
    }
    return length_fixed_header_buf[0];
}





PacketReceiver::PacketReceiver(std::map<PacketType,ConnectPacketFactory*> * factories): _packet_factories(factories) {
//   this->_packet_factories=factories;
}

RawPacket* PacketReceiver::read_next(int socket_fd) {
    // read fixed header
    unsigned char control_fixed_header_buf[1];
    if(read(socket_fd, control_fixed_header_buf, 1) != 1){
        err("Cant read mqtt control fixed header");
    }
    unsigned char first_byte = control_fixed_header_buf[0];
    printf("fixed header first byte:\n");
    Utils::print_bits(first_byte);

//    bool[4] _specific_flags;
    unsigned char specific_flags =eval_specific_flags(first_byte);
    printf("specific flags:\n");
    Utils::print_bits(specific_flags);

    PacketType packet_type =eval_packet_type(first_byte);
    int length =eval_length(socket_fd);
    printf("packet len: %d",length);

    char data_buf[length];
    if(read(socket_fd, data_buf, length) != length){
        err("Cant read packet _data");
    }

    printf("packet data: %s",data_buf);


    RawPacket* rawPacket = new RawPacket(packet_type,specific_flags,length,data_buf);
    ConnectPacketFactory *factory  = _packet_factories->at(packet_type);
    ConnectPacket* connect_packet = factory->create(rawPacket);
    return connect_packet;
}





