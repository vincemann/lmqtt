//
// Created by vince on 06.04.21.
//



#include <unistd.h>
#include <map>
#include <stdio.h>
#include <list>

#include "PacketIOManager.h"
#include "exception/PacketIOException.h"
#include "../packets/PacketType.h"
#include "../util/Utils.h"





static void err(const char* msg){
    throw new PacketIOException(msg);
}

static unsigned char eval_packet_type_value(PacketType packetType){
    switch (packetType) {
        case CONNECT:
            return 1;
    }
    err("unknown packet _type");
}


static PacketType eval_packet_type( unsigned char fixed_header_byte){
    unsigned char mask = Utils::create_bit_mask(4, 7);
    unsigned char packet_type_val = Utils::reverse_bits(mask & fixed_header_byte);


    printf("packet _type bits:\n");
    Utils::print_bits(packet_type_val);
    printf("packet _type resulting number: %d\n",packet_type_val);


    switch (packet_type_val) {
        case 1:
            return PacketType::CONNECT;
    }
    err("unknown packet _type");
}

static unsigned char eval_specific_flags(/*bool[4] result,*/ unsigned char fixed_header_byte){
    unsigned char mask = Utils::create_bit_mask(0, 3);
    unsigned char specific_flags = mask & fixed_header_byte;
    return specific_flags;
//    for (int i =0; i < 4;i++){
//        bool bit = (specific_flags >> i) & 1;
//        result[i] = bit;
//    }
}

static unsigned int eval_packet_length(int _conn_fd){
    // for now just support small sizes
    unsigned char length_fixed_header_buf[1];
    if(read(_conn_fd, length_fixed_header_buf, 1) != 1){
        err("Cant read _length fixed header");
    }
    return length_fixed_header_buf[0];
}


void PacketIOManager::sendPacket(RawPacket *packet) {

    // sendPacket first fixed header byte
    // needs to be reversed bc specs want network endianess on byte level
    unsigned char control_fixed_header [] = {
            Utils::reverse_bits(
                    packet->getSpecificFlags()
                    | eval_packet_type_value(packet->getType())
            )
    };
    if (write(_conn_fd,&control_fixed_header,1) != 1){
        err("cant sendPacket control_fixed_header");
    }
    // sendPacket length
    unsigned char len = packet->getLength();
    unsigned char length_fixed_header [] = { len };
    if (write(_conn_fd,&length_fixed_header,1) != 1){
        err("cant sendPacket length_fixed_header");
    }
    // sendPacket data
    if (write(_conn_fd,packet->getData(),packet->getLength()) != packet->getLength()){
        err("cant sendPacket packet data");
    }
    _session->getPacketsSent()->insert(packet);

}


RawPacket* PacketIOManager::read_packet() {
    // read fixed header
    unsigned char control_fixed_header_buf[1];
    if(read(_conn_fd, control_fixed_header_buf, 1) != 1){
        err("Cant read mqtt control fixed header");
    }
    unsigned char first_byte = control_fixed_header_buf[0];
    printf("fixed header first byte:\n");
    Utils::print_bits(first_byte);

//    bool[4] _specificFlags;
    unsigned char specific_flags =eval_specific_flags(first_byte);
    printf("specific flags:\n");
    Utils::print_bits(specific_flags);

    PacketType packet_type =eval_packet_type(first_byte);
    int length = eval_packet_length(_conn_fd);
    printf("packet len: %d\n",length);

    char data_buf[length];
    if(read(_conn_fd, data_buf, length) != length){
        err("Cant read packet data");
    }

    printf("packet data: %s\n",data_buf);


    RawPacket* raw_packet = new RawPacket(packet_type, specific_flags, length, data_buf);
    PacketParser *parser  = _packet_parsers->at(packet_type);
    RawPacket* parsed_packet = parser->parse(raw_packet);
    _session->getPacketsReceived()->insert(parsed_packet);
}



PacketIOManager::PacketIOManager(Session *session, int connFd,
                                 std::map<PacketType, PacketParser *> *packetParsers) : _session(session),
                                                                                        _conn_fd(connFd),
                                                                                        _packet_parsers(
                                                                                                packetParsers) {}





