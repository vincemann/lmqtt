//
// Created by vince on 10.09.21.
//

#include "Subscription.h"

Subscription::Subscription(char *topic, unsigned long lastMsgIdConsumed, unsigned short qos) : topic(topic),
                                                                                               last_msg_id_consumed(
                                                                                                       lastMsgIdConsumed),
                                                                                               qos(qos) {}

char *Subscription::getTopic() const {
    return topic;
}

unsigned long Subscription::getLastMsgIdConsumed() const {
    return last_msg_id_consumed;
}

unsigned short Subscription::getQos() const {
    return qos;
}
