//
// Created by vince on 23.09.21.
//

#include "QosMessageContainer.h"

QosMessageContainer::QosMessageContainer(char *msg, unsigned char qos, int id, char *topic)
        : value(msg), qos(qos), id(id), topic(topic) {}

char *QosMessageContainer::getValue() const {
    return value;
}

QosMessageContainer::~QosMessageContainer() {
    delete value;
}

int QosMessageContainer::getId() const {
    return id;
}

unsigned char QosMessageContainer::getQos() const {
    return qos;
}

char *QosMessageContainer::getTopic() const {
    return topic;
}

QosMessageContainer::QosMessageContainer(PublishPacket *publishPacket)
        : value(publishPacket->getMsg()), qos(publishPacket->getQos()), id(publishPacket->getPacketId()), topic(publishPacket->getTopic())
{


}
