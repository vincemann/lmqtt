//
// Created by vince on 07.04.21.
//


#include <stdio.h>
#include <iostream>


#include "../con/Connection.h"
#include "exception/IllegalSessionStateException.h"
#include "exception/InvalidPacketException.h"
#include "../packets/ConnectAckPacket.h"
#include "../io/PacketIOManager.h"
#include "../session/ServersClientInfo.h"
#include "../packets/factories/ConnectAckPacketFactory.h"
#include "ConnectPacketHandler.h"
#include "../session/ServersClientInfoRepository.h"




void ConnectPacketHandler::connAck(int errorCode, unsigned char cleanSessionFlag){
    ConnectAckPacket *connectAckPacket = getConnectAckPacketFactory()->create(errorCode,cleanSessionFlag);
    _packetIo->sendPacket(connectAckPacket);
}

void ConnectPacketHandler::initServerSession(unsigned char cleanSession, char * clientId){
    if (cleanSession == 0)
    {
        ServersClientInfo* session = _sessionRepository->load(clientId);
        if (session == nullptr)
        {
            std::cout << "did not find session file for client id" << clientId << "\n";
            std::cout << "creating it" << "\n";
            char* duplicatedClientId = strdup(clientId);
            session = new ServersClientInfo(duplicatedClientId);
            _sessionRepository->save(session);
            std::cout << "new session: " << session << "\n";
        } else{
            std::cout << "have found session file for client id: " << clientId << ": " << session <<"\n";
        }
        serverConnection->serversClientInfo = session;
    }
}


void ConnectPacketHandler::handle(RawPacket *rawPacket) {
    ConnectPacket* packet = static_cast<ConnectPacket*>(rawPacket);
    assertSpecificFlagsZero(packet);

    printf("handling connect rawPacket:\n");
    if (serverConnection->_packetsReceived->size() != 1){
        throw IllegalSessionStateException("received more than one Connect Packet");
    }
    if (strcmp(packet->getProtocolName(), "MQTT") != 0){
        throw InvalidPacketException("invalid protocol name");
    }

    if (packet->getProtocolLevel() != 4){
        connAck(0x1,packet->getCleanSession());
        throw InvalidPacketException("invalid protocol level");
    }

    if (packet->getReservedBit() != 0){
        throw InvalidPacketException("reserved bit must not be set");
    }


    if (packet->getWillFlag()){
        if (packet->getWillQos() == 0x3){
            throw InvalidPacketException("Invalid Will QOS value 3");
        }
    } else{
        if (packet->getWillQos() != 0x0){
            throw InvalidPacketException("Invalid Will QOS value, must be 0 when willFlag is ß");
        }
        if(packet->getWillRetain() != 0){
            throw InvalidPacketException("Invalid Will Retain value, must be 0 when willFlag is ß");
        }
    }
    char* clientId = packet->getClientId();
    if (clientId == nullptr){
        throw InvalidPacketException("No Client id specified");
    }
    if (strlen(clientId) == 0){
        connAck(0x1,packet->getCleanSession());
        throw InvalidPacketException( "Server Side ClientId generation unsupported");
    }
    if ( (strlen(clientId) > 23) || (strlen(clientId) < 1) ){
        throw InvalidPacketException("Invalid Client id size");
    }

    if (! Utils::isAlNum(clientId) ){
        throw InvalidPacketException("Client id must be alphanumerical");
    }

    
    printf("%s\n","valid connect Clients packet received, initializing session");
    unsigned char cleanSession = packet->getCleanSession();


    // init server session
    initServerSession(cleanSession, clientId);
    connAck(0x0, cleanSession);

    if (packet->getCleanSession() == 0){
        // sending all updates
        sendUnconsumedMessages();
    } else{
        // todo impl removal
    }



}

ConnectAckPacketFactory *ConnectPacketHandler::getConnectAckPacketFactory() const {
    return _connectAckPacketFactory;
}


ConnectPacketHandler::ConnectPacketHandler(ServerConnection *connectionSession, PacketIOManager *packetIo,
                                           ConnectAckPacketFactory *connectAckPacketFactory,
                                           ServersClientInfoRepository *sessionRepository,
                                           ServerTopicRepository *topicRepository,
                                           PublishPacketFactory *publishPacketFactory)
        : PacketHandler(packetIo), _connectAckPacketFactory(connectAckPacketFactory), _sessionRepository(
                                                   sessionRepository), serverConnection(connectionSession),
          topicRepository(topicRepository), publishPacketFactory(publishPacketFactory) {}

void ConnectPacketHandler::sendUnconsumedMessages() {
    ServersClientInfo* serversClientInfo = serverConnection->serversClientInfo;
    for (const auto &subscription : *serversClientInfo->subscriptions){
        Topic* topic = topicRepository->loadTopic(subscription->getTopic());
        std::vector<ServerMessageContainer*>* messages=
                topicRepository->consumeMessagesStartingFromId(topic->getValue(), subscription->getLastMsgIdConsumed());
        for (const auto &msg : *messages){
            PublishPacket* publishPacket = publishPacketFactory->create(
                    subscription->getQos(), 0, topic->getValue(), msg->getMsg(), 0
            );
            if ( subscription->getQos() == 0){
                _packetIo->sendPacket(publishPacket);
                subscription->setLastMsgIdConsumed(subscription->getLastMsgIdConsumed() +1 );
            } else if(subscription->getQos() == 1){
                // todo impl with Retransmission Handler
                // put logic for subscription update into puback handler
            }
        }
    }
}





