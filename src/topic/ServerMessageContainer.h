//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_SERVERMESSAGECONTAINER_H
#define LMQTT__SERVER_SERVERMESSAGECONTAINER_H


class ServerMessageContainer {
    unsigned long _id;
    unsigned long _unconsumed_user_count;
    char* _msg;
public:
    ServerMessageContainer(unsigned long id, unsigned long unconsumedUserCount, char *msg);
    ServerMessageContainer(char *msg);

    unsigned long getId() const;

    int getUnconsumedUserCount() const;

    char *getMsg() const;

    void setId(unsigned long id);

    void setUnconsumedUserCount(unsigned long unconsumedUserCount);

    void setMsg(char *msg);
};


#endif //LMQTT__SERVER_SERVERMESSAGECONTAINER_H
