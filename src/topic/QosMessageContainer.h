//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_QOSMESSAGECONTAINER_H
#define LMQTT__SERVER_QOSMESSAGECONTAINER_H


#include <PublishPacket.h>

class QosMessageContainer {
private:
    char *value;
    int id;
    unsigned char qos;
    char* topic;
public:
    QosMessageContainer(char *msg, unsigned char qos, int id, char *topic);
    QosMessageContainer(PublishPacket* publishPacket);

    char *getValue() const;

    int getId() const;

    unsigned char getQos() const;

    char *getTopic() const;

    virtual ~QosMessageContainer();

};


#endif //LMQTT__SERVER_QOSMESSAGECONTAINER_H
