//
// Created by vince on 23.04.21.
//

#ifndef LMQTT__SERVER_PACKETFACTORY_H
#define LMQTT__SERVER_PACKETFACTORY_H


#include <string.h>

#include "exception/PacketCreationException.h"

//todo add template
//template <class P>
class PacketFactory {
    virtual RawPacket *create(RawPacket *raw_packet) = 0;



    static char* createUtf8Payload(const char *pPayload) {
        // todo check for wrong encoding chars -> close connection
        // remove trailing nullbyte
        int len = strlen(pPayload) - 1;
        if (len > 0xffff) {
            throw new PacketCreationException("utf8 payload too long");
        }
        len = (unsigned short) len;
        char* pData = malloc(len + 2);
        // add len
        memcpy(pData, len, 2);
        // add pData
        memcpy(pData, pPayload, len);
        return pData;
    }
};


#endif //LMQTT__SERVER_PACKETFACTORY_H
