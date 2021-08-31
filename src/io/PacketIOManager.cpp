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


static PacketType evalPacketType(unsigned char fixedHeaderByte) {
    unsigned char mask = Utils::createBitMask(4, 7);
//    unsigned char packetTypeVal = mask & fixedHeaderByte;
    unsigned char packetTypeVal = fixedHeaderByte >> 4;
//    unsigned char packetTypeVal = Utils::reverse_bits(packetTypeValTmp);


    // printf("packet _type bits:\n");
    // Utils::printBits(packetTypeVal);
    // printf("packet _type resulting number: %d\n",packetTypeVal);

    return PacketTypes::evalPacketType(packetTypeVal);
}

static unsigned char evalSpecificFlags(/*bool[4] result,*/ unsigned char fixedHeaderByte) {
    unsigned char mask = Utils::createBitMask(0, 3);
    unsigned char specificFlags = mask & fixedHeaderByte;
//    unsigned char specificFlags = (fixedHeaderByte << 4) >> 4 ;
    return specificFlags;
//    for (int i =0; i < 4;i++){
//        bool bit = (specificFlags >> i) & 1;
//        result[i] = bit;
//    }
}

unsigned int PacketIOManager::evalPacketLength() {
    // for now just support small sizes
    // fixed header second byte
    unsigned char packetLenBuf[1];
    if (read(_connFd, packetLenBuf, 1) != 1) {
        err("Cant read _length fixed header");
    }
    return packetLenBuf[0];
}


void PacketIOManager::sendPacket(RawPacket *packet) {

    std::cout << "sending new packet of type: " << PacketTypes::toString(packet->getType()) << "\n";

    printf("specific flags:\n");
    Utils::printBits(packet->getSpecificFlags());


    printf("packetLen: %d\n", packet->getLength());

    printf("Payload:\n");
    if (packet->getLength() != 0){
        Utils::printChars(packet->getData(), packet->getLength());
    } else{
        printf("Empty\n");
    }

    // sendPacket first fixed header byte
    // needs to be reversed bc specs want network endianess on byte level
    unsigned char firstByte = (PacketTypes::evalPacketTypeValue(packet->getType()) << 4) | packet->getSpecificFlags();
//    unsigned char firstByte = (packet->getSpecificFlags() << 4) | PacketTypes::evalPacketTypeValue(packet->getType());
    unsigned char fixedHeader[] = {
            firstByte
    };
    if (write(_connFd, &fixedHeader, 1) != 1) {
        err("cant sendPacket fixedHeader");
    }
    // sendPacket length
    unsigned int len = packet->getLength();
    unsigned char packetLen[] = {static_cast<unsigned char>(len)};
    if (write(_connFd, &packetLen, 1) != 1) {
        err("cant sendPacket packetLen");
    }

    if (len != 0){
        // sendPacket data
        if (write(_connFd, packet->getData(), packet->getLength()) != packet->getLength()) {
            err("cant sendPacket packet data");
        }
    }
    _connectionSession->_packetsSent->push_back(packet);

}


RawPacket *PacketIOManager::readPacket() {
    // read fixed header
    unsigned char fixedHeader[1];
    if (read(_connFd, fixedHeader, 1) != 1) {
        err("Cant read  fixed header");
    }
    unsigned char fixedHeaderFirstByte = fixedHeader[0];
     printf("fixed header first byte:\n");
     Utils::printBits(fixedHeaderFirstByte);

    //    bool[4] _specificFlags;
    unsigned char specificFlags = evalSpecificFlags(fixedHeaderFirstByte);

    PacketType packetType = evalPacketType(fixedHeaderFirstByte);
    if (packetType == PacketType::UNKNOWN){
        err("unknown packet _type");
    };

    std::cout << "received new packet of type: " << PacketTypes::toString(packetType) << "\n";

    printf("specific flags:\n");
    Utils::printBits(specificFlags);

    unsigned int packetLen = evalPacketLength();
    printf("packetLen: %d\n", packetLen);

    unsigned char *packetDataBuf = 0;
    if (packetLen != 0){
        packetDataBuf = (unsigned char *) malloc(packetLen);
        //    unsigned char packetData[packetLen];
        if (read(_connFd, packetDataBuf, packetLen) != packetLen) {
            err("Cant read packet data");
        }
        // print packet
        printf("Payload:\n");
        Utils::printChars(packetDataBuf, packetLen);
    }else{
        printf("Empty Payload\n");
    }

//    printf("packet data: %s\n",packetData);


    RawPacket *rawPacket = new RawPacket(specificFlags, packetDataBuf, packetLen, packetType);
    PacketParser *parser = _packetParsers->at(packetType);
    RawPacket *parsedPacket = parser->parse(rawPacket);
    _connectionSession->_packetsReceived->push_back(parsedPacket);
    // Utils::printChars(parsedPacket->getData(), parsedPacket->getLength());
    return parsedPacket;
}


PacketIOManager::PacketIOManager(Connection *session, int connFd,
                                 std::map<PacketType, PacketParser *> *packetParsers) : _connectionSession(session),
                                                                                        _connFd(connFd),
                                                                                        _packetParsers(
                                                                                                packetParsers) {}

void PacketIOManager::closeConnection() {
    close(_connFd);
}

PacketIOManager::PacketIOManager() {}





