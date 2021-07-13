//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETTYPE_H
#define LMQTT__SERVER_PACKETTYPE_H

enum PacketType {
    CONNECT,
    CONNACK,
    SUBSCRIBE,
    SUBSCRIBE_ACK,
    DISCONNECT
};

namespace PacketTypes {
    static const char *toString(PacketType PacketType) {
        switch (PacketType) {
            case CONNECT:
                return "CONNECT";
                break;
            case CONNACK:
                return "CONNACK";
                break;
            case SUBSCRIBE:
                return "SUBSCRIBE";
                break;
            case SUBSCRIBE_ACK:
                return "SUBSCRIBE_ACK";
                break;
            case DISCONNECT:
                return "DISCONNECT";
                break;
        }
        return "";
    }
}


#endif //LMQTT__SERVER_PACKETTYPE_H
