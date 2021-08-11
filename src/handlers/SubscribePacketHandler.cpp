//
// Created by vince on 11.08.21.
//

#include <SubscribePacket.h>
#include <InvalidPacketException.h>
#include <SubAckPacket.h>
#include "SubscribePacketHandler.h"

SubscribePacketHandler::SubscribePacketHandler(PacketIOManager *packetIo,
                                               ServerSessionRepository *serverSessionRepository,
                                               ServerConnection *serverConnection,
                                               SubAckPacketFactory *subAckPacketFactory)
        : PacketHandler(packetIo), _serverSessionRepository(serverSessionRepository),
          _serverConnection(serverConnection), _subAckPacketFactory(subAckPacketFactory) {}
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

    char *qos_topic = (char *) malloc(strlen((char*) subscribePacket->getQos()) + strlen(subscribePacket->getTopic()) + 1);
    strcat(qos_topic,(char*) subscribePacket->getQos());
    strcat(qos_topic,subscribePacket->getTopic());
    serverSession->_qos_subscriptions->push_back(qos_topic);
    _serverSessionRepository->save(serverSession);
    SubAckPacket* subAckPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(),(unsigned char) subscribePacket->getQos());
    _packetIo->sendPacket(subAckPacket);
}
