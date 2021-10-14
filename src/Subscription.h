//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_SUBSCRIPTION_H
#define LMQTT__SERVER_SUBSCRIPTION_H


class Subscription {
    char* topic;
    long int last_msg_id_consumed;
    unsigned short qos;

public:
    Subscription(char *topic, long int lastMsgIdConsumed, unsigned short qos);

    char *getTopic() const;

    long int getLastMsgIdConsumed() const;

    unsigned short getQos() const;


    void setLastMsgIdConsumed(long int lastMsgIdConsumed);
};


#endif //LMQTT__SERVER_SUBSCRIPTION_H
