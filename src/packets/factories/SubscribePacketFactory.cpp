//
// Created by derdoc on 7/4/21.
//

#include "SubscribePacketFactory.h"

SubscribePacket *
SubscribePacketFactory::create(unsigned short packetId, unsigned short topicLength,
                               char *topic, unsigned char qos) {
    unsigned char specificFlags = 2;
    unsigned int payloadLen = 2 + 2 + topicLength + 1;
    unsigned char *payload = new unsigned char[payloadLen - 1];
    if ( (qos > 3) || (qos < 0) ){
        throw PacketCreationException("invalid QoS value");
    }

    memcpy(payload, &packetId, sizeof(packetId));
    memcpy(payload + 2, &topicLength, sizeof(topicLength));
    memcpy(payload + 4, &topic, sizeof(topicLength));
    for (int i = 0; i < topicLength; ++i) {
        payload[5 + i] = topic[i];
    }
    payload[topicLength - 1] = qos;
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, SUBSCRIBE);
    return new SubscribePacket(rawPacket, packetId, topicLength, topic, qos);
}
