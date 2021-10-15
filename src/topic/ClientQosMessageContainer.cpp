//
// Created by vince on 23.09.21.
//

#include "ClientQosMessageContainer.h"

ClientQosMessageContainer::ClientQosMessageContainer(char *msg, unsigned char qos, int id, char *topic)
        : value(msg), qos(qos), id(id), topic(topic) {}

char *ClientQosMessageContainer::getValue() const {
    return value;
}

ClientQosMessageContainer::~ClientQosMessageContainer() {
    delete value;
}

int ClientQosMessageContainer::getId() const {
    return id;
}

unsigned char ClientQosMessageContainer::getQos() const {
    return qos;
}

char *ClientQosMessageContainer::getTopic() const {
    return topic;
}

ClientQosMessageContainer::ClientQosMessageContainer(PublishPacket *publishPacket)
        : value(publishPacket->getMsg()), qos(publishPacket->getQos()), id(publishPacket->getPacketId()), topic(publishPacket->getTopic())
{


}
