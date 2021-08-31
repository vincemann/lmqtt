//
// Created by vince on 11.08.21.
//

#include <SubscribePacket.h>
#include <InvalidPacketException.h>
#include <SubAckPacket.h>
#include "SubscribePacketHandler.h"
#include <stdlib.h>

SubscribePacketHandler::SubscribePacketHandler(PacketIOManager *packetIo,
                                               ServerSessionRepository *serverSessionRepository,
                                               ServerConnection *serverConnection,
                                               SubAckPacketFactory *subAckPacketFactory,
                                               TopicRepository *topicRepository)
        : PacketHandler(packetIo), _serverSessionRepository(serverSessionRepository),
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

    ServerSession* serverSession = _serverConnection->_serverSession;

    // store qos and topic cated together to save space and complexity
    int bufLen = /* qos:*/ sizeof(unsigned char) + strlen(subscribePacket->getTopic()) + 1;
    char *qos_topic = (char *) malloc(bufLen);
    memset(qos_topic,0,bufLen);
    unsigned char qos = subscribePacket->getQos();
    sprintf(qos_topic,"%d",qos);
    sprintf(qos_topic+1,"%s",subscribePacket->getTopic());
//    memcpy(qos_topic+1,subscribePacket->getTopic(), strlen(subscribePacket->getTopic())+1);
    serverSession->_qos_subscriptions->push_back(qos_topic);
    _serverSessionRepository->save(serverSession);
    Topic* storedTopic = topicRepository->loadTopic(subscribePacket->getTopic());
    if (storedTopic == 0){
        // send err ret code and quit connection
        SubAckPacket* errPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(),0x80);
        _packetIo->sendPacket(errPacket);
        throw InvalidPacketException("Topic does not exist");
    } else{
        storedTopic->_subscribed_users_count += 1;
        SubAckPacket* successPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(), (unsigned char) subscribePacket->getQos());
        _packetIo->sendPacket(successPacket);
        // todo send publish msg'es to let client consume all msges of topic
    }

}
