//
// Created by vince on 23.09.21.
//

#include "ClientMessageContainer.h"

ClientMessageContainer::ClientMessageContainer(char *msg) : msg(msg) {}

char *ClientMessageContainer::getMsg() const {
    return msg;
}

ClientMessageContainer::~ClientMessageContainer() {
    delete msg;
}

unsigned long ClientMessageContainer::getId() const {
    return id;
}
