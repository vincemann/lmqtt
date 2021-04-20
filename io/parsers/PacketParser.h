//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_PACKETPARSER_H
#define LMQTT__SERVER_PACKETPARSER_H

//template <class P>
class PacketParser {
public:
    virtual RawPacket* parse(RawPacket* raw_packet) = 0;
    /*
     * give me pointer into RawPacket.data buf from where i should start reading
     * I'll increment your pointer until its behind utf8 payload and return
     * utf-8 payload as null terminated copied string
     */
    unsigned short getUf8PayloadLen(char* pData);
};



#endif //LMQTT__SERVER_PACKETPARSER_H
