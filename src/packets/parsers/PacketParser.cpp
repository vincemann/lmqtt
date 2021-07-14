//
// Created by vince on 27.04.21.
//

#include "PacketParser.h"
#include "../RawPacket.h"
#include "../../util/Utils.h"
#include "exception/PacketParsingException.h"
#include <string.h>

char *PacketParser::extractUtf8Payload(unsigned char **ppData, bool incrementPointer) {
    // todo check for wrong encoding chars -> close connection
    unsigned char *pData = *ppData;
    unsigned short len = getUf8PayloadLen(pData);
    unsigned char payload[len + 1];
//    pData+=sizeof(unsigned short);
    Utils::extractSubArray(pData+2, payload, len);
    // check for null bytes
    for (int i = 0; i < len - 1; ++i) {
        unsigned char c = payload[i];
        if (c == '\0') {
            throw PacketParsingException("payload must not contain nullbytes");
        }
    }
    // add trailing null byte
    payload[len] = '\0';
    if (incrementPointer) {
        *ppData = pData + (len + sizeof(unsigned short));
    }
    return strdup((char*)payload);
}

unsigned short PacketParser::getUf8PayloadLen(unsigned char *pData)  {
    // read length
    unsigned short len = (pData[1] << 8) | pData[0];
    return len;
}

PacketParser::~PacketParser() {

}

