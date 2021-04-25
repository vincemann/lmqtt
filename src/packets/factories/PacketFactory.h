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
#include "../Payload.h"

//todo add template
//template <class P>
class PacketFactory {
//    virtual RawPacket *create(RawPacket *raw_packet) = 0;
public:

    // merges payloads into buf and returns it
    // call like that:
    // mergePayloads(dstBuf,(Payload*[]){val1,val2,val3,val4},4);
    // also deletes the payloads
    static unsigned char* mergePayloads(int* bufSize, const Payload** values, int argCount){
        unsigned int offset = 0;
        int dstSize = 0;
        for (int i = 0; i < argCount; ++i) {
            const Payload *payload = values[i];
            dstSize += payload->getSize();
        }
        *bufSize=dstSize;
        unsigned char *dst = malloc(dstSize);
        // pointer cant have value 0xf, so its a acceptable end condition
        for (int i = 0; i < argCount; ++i) {
            const Payload *payload = values[i];
            if (payload == 0){
                continue;
            }
            if (payload->prependSize){
                size_t sizeLength = sizeof(unsigned short);
                memcpy(dst+offset, payload->_dataSize, sizeLength);
            }
            // nullbytes of payload strings are cut off here bc size does not contain them
            memcpy(dst+offset, payload->_data, payload->_dataSize);
            offset += payload->getSize();
            delete payload;
        }
        return dst;
    }

//    // call like that:
//    // only use char* and unsigned char*
//    // memcpyMergeStrings(dst,(void*[]){val1,val2,val3,val4,0xf});
//    static void mergeStrings(void* dst, const void** values, int argCount){
//        unsigned int offset = 0;
//        // pointer cant have value 0xf, so its a acceptable end condition
//        for (int i = 0; i < argCount; ++i) {
//            const void *value = values[i];
//            if (value == 0){
//                continue;
//            }
//            // strlen does not count nullbyte -> nullbytes not copied
//            memcpy(dst+offset,value,strlen((const char*)value));
//            offset += strlen((const char*)value);
//        }
//    }


    // Payload strings wont have trailing nullbytes
    static Payload* createUtf8Payload(const char *payloadData) {
        // todo check for wrong encoding chars -> close connection
        // strlen does not count nullbyte -> null byte will be cut off
        int len = strlen(payloadData);
        if (len > 0xffff) {
            throw new PacketCreationException("utf8 payloadData too long");
        }
        len = (unsigned short) len;
        char* data = (char*)malloc(sizeof(char) * len);
        // add data
        strncpy(data, payloadData, len);
        Payload* payload = new Payload((unsigned char)data, len, true);
        return payload;
    }
};


#endif //LMQTT__SERVER_PACKETFACTORY_H
