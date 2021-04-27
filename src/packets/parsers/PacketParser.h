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


    unsigned short getUf8PayloadLen(unsigned char *pData);


    /*
     * give me pointer into RawPacket.data buf from where i should start reading
     * I'll increment your pointer until its behind utf8 payload and return
     * utf-8 payload as null terminated copied string
     */
    char *extractUtf8Payload(unsigned char **ppData, bool incrementPointer = true);

};



#endif //LMQTT__SERVER_PACKETPARSER_H
