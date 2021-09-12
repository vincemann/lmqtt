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
    UNSUBSCRIBE,
    UNSUB_ACK,
    DISCONNECT,
    PUBLISH,
    PUB_ACK,
    UNKNOWN
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
            case UNSUBSCRIBE:
                return "UNSUBSCRIBE";
                break;
            case UNSUB_ACK:
                return "UNSUB_ACK";
                break;
            case DISCONNECT:
                return "DISCONNECT";
                break;
            case PUBLISH:
                return "PUBLISH";
                break;
        }
        return "UNKNOWN";
    }

    static unsigned char evalPacketTypeValue(PacketType packetType) {
        switch (packetType) {
            case CONNECT:
                return 1;
            case CONNACK:
                return 2;
            case SUBSCRIBE:
                return 8;
            case SUBSCRIBE_ACK:
                return 9;
            case UNSUBSCRIBE:
                return 10;
            case UNSUB_ACK:
                return 11;
            case PUBLISH:
                return 4;
            case DISCONNECT:
                return 14;
        }
        return -1;
    }

    static PacketType evalPacketType(unsigned char packetTypeVal) {
        switch (packetTypeVal) {
            case 1:
                return PacketType::CONNECT;
            case 2:
                return PacketType::CONNACK;
            case 4:
                return PacketType::PUBLISH;
            case 8:
                return PacketType::SUBSCRIBE;
            case 9:
                return PacketType::SUBSCRIBE_ACK;
            case 10:
                return PacketType::UNSUBSCRIBE;
            case 11:
                return PacketType::UNSUB_ACK;
            case 14:
                return PacketType::DISCONNECT;
        }
        return PacketType::UNKNOWN;
    }
}


#endif //LMQTT__SERVER_PACKETTYPE_H
