//
// Created by vince on 10.09.21.
//

#include <Utils.h>
#include "PublishPacketFactory.h"

PublishPacket*
PublishPacketFactory::create(unsigned short qos, unsigned char retainFlag, char *topic,
                             char *msg, unsigned char dupFlag) {


    unsigned char specificFlags = (dupFlag << 3) | (qos << 1) | retainFlag;
    printf("specific flags:\n");
    Utils::printBits(specificFlags);

    Payload* topicPayload = createUtf8Payload(topic);

    Payload* packetIdPayload = 0;
    unsigned short packetId = -1;
    if (qos > 0){
        srand(time(NULL));   // Initialization, should only be called once.
        packetId = (unsigned short) rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
        printf("qos is > 0 so gen packet id:%d\n",packetId);
        packetIdPayload = new Payload(packetId);
    }

    Payload* msgPayload = createUtf8Payload(msg);

    int payloadLen;
    const Payload* toMerge[] = {topicPayload, packetIdPayload,msgPayload};
    unsigned char* payload = mergePayloads(&payloadLen, toMerge, 3);

//    printf("payload:%.*s\n", *payloadLen, (char*) payload);

    RawPacket *rawPacket = new RawPacket(specificFlags,payload,payloadLen,PUBLISH);
    return new PublishPacket(rawPacket, dupFlag, qos, retainFlag, topic, packetId, msg);
}
