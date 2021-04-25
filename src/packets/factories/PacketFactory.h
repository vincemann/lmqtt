//
// Created by vince on 23.04.21.
//

#ifndef LMQTT__SERVER_PACKETFACTORY_H
#define LMQTT__SERVER_PACKETFACTORY_H


#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "exception/PacketCreationException.h"

//todo add template
//template <class P>
class PacketFactory {
//    virtual RawPacket *create(RawPacket *raw_packet) = 0;
public:
    // call like that:
    // memcpyMergeStrings(dst,(void*[]){val1,val2,val3,val4,0xf});
    //
    static void memcpyMergeStrings(void* dst, const void** values, int argCount){
        unsigned int offset = 0;
        // pointer cant have value 0xf, so its a acceptable end condition
        for (int i = 0; i < argCount; ++i) {
            const void *value = values[i];
            if (value == 0){
                continue;
            }
            memcpy(dst+offset,value,strlen((const char*)value));
            offset += strlen((const char*)value);
        }
    }


    // still has trailing nullbyte
    static char* createUtf8Payload(const char *pPayload) {
        // todo check for wrong encoding chars -> close connection
        // strlen does not count nullbyte
        int len = strlen(pPayload) +1;
        if (len > 0xffff) {
            throw new PacketCreationException("utf8 payload too long");
        }
        len = (unsigned short) len;
        char* pData = (char*)malloc(sizeof(char) * (len + 2));
        // add len
        memcpy(pData, &len, 2);
        // add pData
        strncpy(pData+2,pPayload,len);
        return pData;
    }
};


#endif //LMQTT__SERVER_PACKETFACTORY_H
