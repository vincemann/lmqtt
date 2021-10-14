//
// Created by vince on 01.04.21.
//



#ifndef LMQTT__SERVER_PACKETTYPE_H
#define LMQTT__SERVER_PACKETTYPE_H

enum PacketType {
    CONNECT,
    CONNECT_ACK,
    SUBSCRIBE,
    SUBSCRIBE_ACK,
    UNSUBSCRIBE,
    UNSUB_ACK,
    DISCONNECT,
    PUBLISH,
    PUBLISH_ACK,
    UNKNOWN
};

namespace PacketTypes {
    static const char *toString(PacketType PacketType) {
        switch (PacketType) {
            case CONNECT:
                return "CONNECT";
            case CONNECT_ACK:
                return "CONNECT_ACK";
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
            case PUBLISH_ACK:
                return "PUBLISH_ACK";
                break;
        }
        return "UNKNOWN";
    }

    static unsigned char evalPacketTypeValue(PacketType packetType) {
        switch (packetType) {
            case CONNECT:
                return 1;
            case CONNECT_ACK:
                return 2;
            case PUBLISH:
                return 3;
            case PUBLISH_ACK:
                return 4;
            case SUBSCRIBE:
                return 8;
            case SUBSCRIBE_ACK:
                return 9;
            case UNSUBSCRIBE:
                return 10;
            case UNSUB_ACK:
                return 11;
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
                return PacketType::CONNECT_ACK;
            case 3:
                return PacketType::PUBLISH;
            case 4:
                return PacketType::PUBLISH_ACK;
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
