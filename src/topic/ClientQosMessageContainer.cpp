//
// Created by vince on 23.09.21.
//

#include "ClientQosMessageContainer.h"

ClientQosMessageContainer::ClientQosMessageContainer(char *msg, unsigned char qos, unsigned long id, char *topic)
        : value(msg), qos(qos), id(id), topic(topic) {}

char *ClientQosMessageContainer::getValue() const {
    return value;
}

ClientQosMessageContainer::~ClientQosMessageContainer() {
    delete value;
}

unsigned long ClientQosMessageContainer::getId() const {
    return id;
}

unsigned char ClientQosMessageContainer::getQos() const {
    return qos;
}

char *ClientQosMessageContainer::getTopic() const {
    return topic;
}
