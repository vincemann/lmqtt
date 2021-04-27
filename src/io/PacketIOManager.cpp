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
#include "../Session.h"





static void err(const char* msg){
    throw new PacketIOException(msg);
}

static unsigned char evalPacketTypeValue(PacketType packetType){
    switch (packetType) {
        case CONNECT:
            return 1;
    }
    err("unknown packet _type");
}


static PacketType evalPacketType(unsigned char fixed_header_byte){
    unsigned char mask = Utils::createBitMask(4, 7);
    unsigned char packet_type_val = Utils::reverse_bits(mask & fixed_header_byte);


    printf("packet _type bits:\n");
    Utils::printBits(packet_type_val);
    printf("packet _type resulting number: %d\n",packet_type_val);


    switch (packet_type_val) {
        case 1:
            return PacketType::CONNECT;
    }
    err("unknown packet _type");
}

static unsigned char evalSpecificFlags(/*bool[4] result,*/ unsigned char fixed_header_byte){
    unsigned char mask = Utils::createBitMask(0, 3);
    unsigned char specific_flags = mask & fixed_header_byte;
    return specific_flags;
//    for (int i =0; i < 4;i++){
//        bool bit = (specific_flags >> i) & 1;
//        result[i] = bit;
//    }
}

static unsigned int evalPacketLength(int _conn_fd){
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
                    | evalPacketTypeValue(packet->getType())
            )
    };
    if (write(_conn_fd,&control_fixed_header,1) != 1){
        err("cant sendPacket control_fixed_header");
    }
    // sendPacket length
    unsigned int len = packet->getLength();
    unsigned char length_fixed_header [] = { len };
    if (write(_conn_fd,&length_fixed_header,1) != 1){
        err("cant sendPacket length_fixed_header");
    }
    // sendPacket data
    if (write(_conn_fd,packet->getData(),packet->getLength()) != packet->getLength()){
        err("cant sendPacket packet data");
    }
    _session->_packets_sent->push_back(packet);

}


RawPacket* PacketIOManager::readPacket() {
    // read fixed header
    unsigned char controlFixedHeaderBuf[1];
    if(read(_conn_fd, controlFixedHeaderBuf, 1) != 1){
        err("Cant read mqtt control fixed header");
    }
    unsigned char firstByte = controlFixedHeaderBuf[0];
    printf("fixed header first byte:\n");
    Utils::printBits(firstByte);

//    bool[4] _specificFlags;
    unsigned char specific_flags = evalSpecificFlags(firstByte);
    printf("specific flags:\n");
    Utils::printBits(specific_flags);

    PacketType packet_type = evalPacketType(firstByte);
    unsigned int packetLen = evalPacketLength(_conn_fd);
    printf("packetLen: %d\n", packetLen);

    unsigned char packetData[packetLen];
    if(read(_conn_fd, packetData, packetLen) != packetLen){
        err("Cant read packet data");
    }

    Utils::printChars(packetData, packetLen);
//    printf("packet data: %s\n",packetData);


    RawPacket* rawPacket = new RawPacket(specific_flags, packetData, packetLen, packet_type);
    PacketParser *parser  = _packet_parsers->at(packet_type);
    RawPacket* parsedPacket = parser->parse(rawPacket);
    _session->_packets_received->push_back(parsedPacket);
    return parsedPacket;
}



PacketIOManager::PacketIOManager(Session *session, int connFd,
                                 std::map<PacketType, PacketParser *> *packetParsers) : _session(session),
                                                                                        _conn_fd(connFd),
                                                                                        _packet_parsers(packetParsers) {}





