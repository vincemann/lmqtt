//
// Created by vince on 10.09.21.
//

#include <Utils.h>
#include "PublishPacketFactory.h"




PublishPacket *
PublishPacketFactory::create(unsigned short qos, unsigned char retainFlag, char *topic,
                             char *msg, unsigned char dupFlag, int packetId) {


    unsigned char specificFlags = (dupFlag << 3) | (qos << 1) | retainFlag;
//    specificFlags = specificFlags | (3 << 4);
    printf("specific flags:\n");
    Utils::printBits(specificFlags);

    Payload *topicPayload = createUtf8Payload(topic);

    Payload *packetIdPayload = 0;
    int finalPacketId = packetId;
    if (qos > 0) {
        if (packetId == -1) {
            finalPacketId = Utils::gen_random_packet_id();
        } else {
            printf("packet id supplied: %d, not generating new one\n", finalPacketId);
        }
        packetIdPayload = new Payload(finalPacketId);
    }

    Payload *msgPayload = createUtf8Payload(msg);

    int payloadLen;
    const Payload *toMerge[] = {topicPayload, packetIdPayload, msgPayload};
    unsigned char *payload = mergePayloads(&payloadLen, toMerge, 3);

//    printf("payload:%.*s\n", *payloadLen, (char*) payload);

    RawPacket *rawPacket = new RawPacket(specificFlags, payload, payloadLen, PUBLISH);
    return new
            PublishPacket(rawPacket, dupFlag, qos, retainFlag, topic, finalPacketId, msg
    );
}
