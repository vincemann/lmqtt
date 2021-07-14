//
// Created by vince on 06.04.21.
//

#include <unistd.h>
#include <map>
#include <stdio.h>
#include <list>
#include <iostream>


#include "PacketIOManager.h"
#include "exception/PacketIOException.h"


static void err(const char *msg) {
    throw PacketIOException(msg);
}

static unsigned char evalPacketTypeValue(PacketType packetType) {
    switch (packetType) {
        case CONNECT:
            return 1;
        case CONNACK:
            return 2;
    }
    err("unknown packet _type");
}


static PacketType evalPacketType(unsigned char fixed_header_byte) {
    unsigned char mask = Utils::createBitMask(4, 7);
    unsigned char packet_type_val = Utils::reverse_bits(mask & fixed_header_byte);


    // printf("packet _type bits:\n");
    // Utils::printBits(packet_type_val);
    // printf("packet _type resulting number: %d\n",packet_type_val);


    switch (packet_type_val) {
        case 1:
            return PacketType::CONNECT;
        case 2:
            return PacketType::CONNACK;
    }
    err("unknown packet type");
}

static unsigned char evalSpecificFlags(/*bool[4] result,*/ unsigned char fixed_header_byte) {
    unsigned char mask = Utils::createBitMask(0, 3);
    unsigned char specific_flags = mask & fixed_header_byte;
    return specific_flags;
//    for (int i =0; i < 4;i++){
//        bool bit = (specific_flags >> i) & 1;
//        result[i] = bit;
//    }
}

static unsigned int evalPacketLength(int _conn_fd) {
    // for now just support small sizes
    unsigned char length_fixed_header_buf[1];
    if (read(_conn_fd, length_fixed_header_buf, 1) != 1) {
        err("Cant read _length fixed header");
    }
    return length_fixed_header_buf[0];
}


void PacketIOManager::sendPacket(RawPacket *packet) {

    std::cout << "sending new packet of type: " << PacketTypes::toString(packet->getType()) << "\n";

    printf("specific flags:\n");
    Utils::printBits(packet->getSpecificFlags());


    printf("packetLen: %d\n", packet->getLength());

    printf("Payload:\n");
    Utils::printChars(packet->getData(), packet->getLength());

    // sendPacket first fixed header byte
    // needs to be reversed bc specs want network endianess on byte level
    unsigned char control_fixed_header[] = {
            Utils::reverse_bits(
                    packet->getSpecificFlags()
                    | evalPacketTypeValue(packet->getType())
            )
    };
    if (write(_conn_fd, &control_fixed_header, 1) != 1) {
        err("cant sendPacket control_fixed_header");
    }
    // sendPacket length
    unsigned int len = packet->getLength();
    unsigned char length_fixed_header[] = {static_cast<unsigned char>(len)};
    if (write(_conn_fd, &length_fixed_header, 1) != 1) {
        err("cant sendPacket length_fixed_header");
    }
    // sendPacket data
    if (write(_conn_fd, packet->getData(), packet->getLength()) != packet->getLength()) {
        err("cant sendPacket packet data");
    }
    _connectionSession->_packetsSent->push_back(packet);

}


RawPacket *PacketIOManager::readPacket() {
    // read fixed header
    unsigned char controlFixedHeaderBuf[1];
    if (read(_conn_fd, controlFixedHeaderBuf, 1) != 1) {
        err("Cant read mqtt control fixed header");
    }
    unsigned char firstByte = controlFixedHeaderBuf[0];
    // printf("fixed header first byte:\n");
    // Utils::printBits(firstByte);

//    bool[4] _specificFlags;
    unsigned char specific_flags = evalSpecificFlags(firstByte);

    PacketType packet_type = evalPacketType(firstByte);

    std::cout << "received new packet of type: " << PacketTypes::toString(packet_type) << "\n";

    printf("specific flags:\n");
    Utils::printBits(specific_flags);

    unsigned int packetLen = evalPacketLength(_conn_fd);
    printf("packetLen: %d\n", packetLen);

    unsigned char *packetDataBuf = (unsigned char *) malloc(packetLen);
//    unsigned char packetData[packetLen];
    if (read(_conn_fd, packetDataBuf, packetLen) != packetLen) {
        err("Cant read packet data");
    }

    // print packet
    printf("Payload:\n");
    Utils::printChars(packetDataBuf, packetLen);
//    printf("packet data: %s\n",packetData);


    RawPacket *rawPacket = new RawPacket(specific_flags, packetDataBuf, packetLen, packet_type);
    PacketParser *parser = _packet_parsers->at(packet_type);
    RawPacket *parsedPacket = parser->parse(rawPacket);
    _connectionSession->_packetsReceived->push_back(parsedPacket);
    // Utils::printChars(parsedPacket->getData(), parsedPacket->getLength());
    return parsedPacket;
}


PacketIOManager::PacketIOManager(Connection *session, int connFd,
                                 std::map<PacketType, PacketParser *> *packetParsers) : _connectionSession(session),
                                                                                        _conn_fd(connFd),
                                                                                        _packet_parsers(
                                                                                                packetParsers) {}

void PacketIOManager::closeConnection() {
    close(_conn_fd);
}

PacketIOManager::PacketIOManager() {}





