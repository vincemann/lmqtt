//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_SUBSCRIPTION_H
#define LMQTT__SERVER_SUBSCRIPTION_H


class Subscription {
    char* topic;
    unsigned long last_msg_id_consumed;
    unsigned short qos;

public:
    Subscription(char *topic, unsigned long lastMsgIdConsumed, unsigned short qos);

    char *getTopic() const;

    unsigned long getLastMsgIdConsumed() const;

    unsigned short getQos() const;
};


#endif //LMQTT__SERVER_SUBSCRIPTION_H
