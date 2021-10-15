//
// Created by vince on 10.09.21.
//

#include "Subscription.h"

Subscription::Subscription(char *topic, int lastMsgIdConsumed, unsigned short qos) : topic(topic),
                                                                                               last_msg_id_consumed(
                                                                                                       lastMsgIdConsumed),
                                                                                               qos(qos) {}

char *Subscription::getTopic() const {
    return topic;
}

int Subscription::getLastMsgIdConsumed() const {
    return last_msg_id_consumed;
}

unsigned short Subscription::getQos() const {
    return qos;
}

void Subscription::setLastMsgIdConsumed(int lastMsgIdConsumed) {
    last_msg_id_consumed = lastMsgIdConsumed;
}
