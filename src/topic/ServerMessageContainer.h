//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_SERVERMESSAGECONTAINER_H
#define LMQTT__SERVER_SERVERMESSAGECONTAINER_H


class ServerMessageContainer {
    long int _id;
    long int _unconsumed_user_count;
    char* _msg;
public:
    ServerMessageContainer(long int id, long int unconsumedUserCount, char *msg);
    ServerMessageContainer(char *msg);

    long int getId() const;

    int getUnconsumedUserCount() const;

    char *getMsg() const;

    void setId(long int id);

    void setUnconsumedUserCount(long int unconsumedUserCount);

    void setMsg(char *msg);
};


#endif //LMQTT__SERVER_SERVERMESSAGECONTAINER_H
