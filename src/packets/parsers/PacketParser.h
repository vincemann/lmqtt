//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_PACKETPARSER_H
#define LMQTT__SERVER_PACKETPARSER_H

#include "../RawPacket.h"
#include "../../util/Utils.h"
#include "exception/PacketParsingException.h"
#include <string.h>

//todo add template
//template <class P>
class PacketParser {
public:
    virtual RawPacket* parse(RawPacket* raw_packet) = 0;

    /*
     * give me pointer into RawPacket.data buf from where i should start reading
     * I'll increment your pointer until its behind utf8 payload and return
     * utf-8 payload as null terminated copied string
     */
    static unsigned short getUf8PayloadLen(unsigned char *pData) {
        // read length
        unsigned short len = (pData[0] << 8) | pData[1];
        return len;
    }



    static char *extractUtf8Payload(unsigned char *p, bool incrementPointer = true) {
        // todo check for wrong encoding chars -> close connection
        unsigned short len = getUf8PayloadLen(p);
        unsigned char payload[len + 1];
        Utils::extractSubArray(p, payload, len);
        // check for null bytes
        for (int i = 0; i < len - 1; ++i) {
            unsigned char c = payload[i];
            if (c == '\0') {
                throw new PacketParsingException("payload must not contain nullbytes");
            }
        }
        // add trailing null byte
        payload[len] = '\0';
        if (incrementPointer) {
            p += len;
        }
        return strdup((char*)payload);
    }

};



#endif //LMQTT__SERVER_PACKETPARSER_H
