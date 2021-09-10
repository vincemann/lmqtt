//
// Created by vince on 11.08.21.
//

#include <SubscribePacket.h>
#include <InvalidPacketException.h>
#include <SubscribeAckPacket.h>
#include "SubscribePacketHandler.h"
#include <stdlib.h>

SubscribePacketHandler::SubscribePacketHandler(PacketIOManager *packetIo,
                                               ServersClientInfoRepository *serverSessionRepository,
                                               ServerConnection *serverConnection,
                                               SubAckPacketFactory *subAckPacketFactory,
                                               ServerTopicRepository *topicRepository)
        : PacketHandler(packetIo), serversClientInfoRepository(serverSessionRepository),
          _serverConnection(serverConnection), _subAckPacketFactory(subAckPacketFactory),
          topicRepository(topicRepository) {}
void SubscribePacketHandler::handle(RawPacket *packet) {
    SubscribePacket* subscribePacket = static_cast<SubscribePacket*>(packet);
    if (subscribePacket->getQos() > 3 || subscribePacket->getQos() < 0){
        //todo return ret code 0x80 to indicate error instead of exception
        throw InvalidPacketException("qos must be 0 - 3 ");
    }

    if (strlen(subscribePacket->getTopic())<=1){
        throw InvalidPacketException("topic len must be > 1");
    }


    Topic* storedTopic = topicRepository->loadTopic(subscribePacket->getTopic());
    if (storedTopic == 0){
        // send err ret code and quit connection
        SubscribeAckPacket* errPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(), 0x80);
        _packetIo->sendPacket(errPacket);
        throw InvalidPacketException("Topic does not exist");
    } else{
        // session is already loaded by connectPacketHandler
        ServersClientInfo* serversClientInfo = _serverConnection->serversClientInfo;

        Subscription* subscription = new Subscription(subscribePacket->getTopic(),storedTopic->getLastMsgIdPublished(),subscribePacket->getQos());
        // saveMsg qos and topic cated together to save space and complexity
//        int bufLen = /* qos:*/ sizeof(unsigned char) + strlen(subscribePacket->getTopic()) + 1;
//        char *qos_topic = (char *) malloc(bufLen);
//        memset(qos_topic,0,bufLen);
//        unsigned char qos = subscribePacket->getQos();
//        sprintf(qos_topic,"%d",qos);
//        sprintf(qos_topic+1,"%s",subscribePacket->getTopic());
        serversClientInfo->subscriptions->push_back(subscription);
        serversClientInfoRepository->save(serversClientInfo);

        topicRepository->subscribe(subscribePacket->getTopic());
        SubscribeAckPacket* successPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(), (unsigned char) subscribePacket->getQos());
        _packetIo->sendPacket(successPacket);
        // todo send publish msg'es to let client consume all msges of topic
    }

}
