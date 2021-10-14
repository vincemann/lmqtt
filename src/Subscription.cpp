//
// Created by vince on 10.09.21.
//

#include "Subscription.h"

Subscription::Subscription(char *topic, long int lastMsgIdConsumed, unsigned short qos) : topic(topic),
                                                                                               last_msg_id_consumed(
                                                                                                       lastMsgIdConsumed),
                                                                                               qos(qos) {}

char *Subscription::getTopic() const {
    return topic;
}

long int Subscription::getLastMsgIdConsumed() const {
    return last_msg_id_consumed;
}

unsigned short Subscription::getQos() const {
    return qos;
}

void Subscription::setLastMsgIdConsumed(long int lastMsgIdConsumed) {
    last_msg_id_consumed = lastMsgIdConsumed;
}
