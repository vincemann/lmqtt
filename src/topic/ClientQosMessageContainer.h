//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H
#define LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H


#include <PublishPacket.h>

class ClientQosMessageContainer {
private:
    char *value;
    long int id;
    unsigned char qos;
    char* topic;
public:
    ClientQosMessageContainer(char *msg, unsigned char qos, long int id, char *topic);
    ClientQosMessageContainer(PublishPacket* publishPacket);

    char *getValue() const;

    long int getId() const;

    unsigned char getQos() const;

    char *getTopic() const;

    virtual ~ClientQosMessageContainer();

};


#endif //LMQTT__SERVER_CLIENTQOSMESSAGECONTAINER_H
