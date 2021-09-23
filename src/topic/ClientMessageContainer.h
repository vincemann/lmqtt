//
// Created by vince on 23.09.21.
//

#ifndef LMQTT__SERVER_CLIENTMESSAGECONTAINER_H
#define LMQTT__SERVER_CLIENTMESSAGECONTAINER_H


class ClientMessageContainer {
private:
    char *msg;
public:
    ClientMessageContainer(char *msg);

    char *getMsg() const;

    virtual ~ClientMessageContainer();

};


#endif //LMQTT__SERVER_CLIENTMESSAGECONTAINER_H
