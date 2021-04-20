//
// Created by vince on 09.04.21.
//


#include "PacketParser.h"




unsigned short PacketParser::getUf8PayloadLen(char *pData) {
    // read length
    unsigned short len = (pData[0] << 8) | pData[1];
    return len;
}
