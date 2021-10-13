//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H
#define LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H


#include <PublishPacket.h>

class ClientQosMessageContainer {
private:
    char *value;
    unsigned long id;
    unsigned char qos;
    char* topic;
public:
    ClientQosMessageContainer(char *msg, unsigned char qos, unsigned long id, char *topic);
    ClientQosMessageContainer(PublishPacket* publishPacket);

    char *getValue() const;

    unsigned long getId() const;

    unsigned char getQos() const;

    char *getTopic() const;

    virtual ~ClientQosMessageContainer();

};


#endif //LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H
