//
// Created by derdoc on 7/4/21.
//

#include "SubscribePacketFactory.h"
#include "PacketType.h"
#include <string.h>

SubscribePacket *
SubscribePacketFactory::create(unsigned short packetId,
                               char *topic, unsigned char qos) {
    unsigned char specificFlags = 2;
    unsigned int topicLength = strlen(topic);
    unsigned int payloadLen = 2 + 2 + topicLength + 1;
    unsigned char *payload = new unsigned char[payloadLen - 1];
    if ( (qos > 3) || (qos < 0) ){
        throw PacketCreationException("invalid QoS value");
    }

    // createUtf8Payload()
    memcpy(payload, &packetId, sizeof(unsigned short));
    payload += sizeof(packetId);

    memcpy(payload, &topicLength, sizeof(unsigned short));
    payload += sizeof(topicLength);

    memcpy(payload, &topic, topicLength);
    payload += topicLength;

    memcpy(payload, &qos, sizeof(qos));
    payload += sizeof(qos);
//    payload[topicLength - 1] = qos;
    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, SUBSCRIBE);
    return new SubscribePacket(rawPacket, packetId, topicLength, topic, qos);
}

