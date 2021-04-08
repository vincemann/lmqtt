//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_PACKETPARSER_H
#define LMQTT__SERVER_PACKETPARSER_H

//template <class P>
class PacketParser {
public:
    virtual RawPacket* parse(RawPacket* raw_packet) = 0;
};


#endif //LMQTT__SERVER_PACKETPARSER_H
