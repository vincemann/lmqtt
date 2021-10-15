//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_SERVERMESSAGECONTAINER_H
#define LMQTT__SERVER_SERVERMESSAGECONTAINER_H


class ServerMessageContainer {
    int _id;
    int _unconsumed_user_count;
    char* _msg;
public:
    ServerMessageContainer(int id, int unconsumedUserCount, char *msg);
    ServerMessageContainer(char *msg);

    int getId() const;

    int getUnconsumedUserCount() const;

    char *getMsg() const;

    void setId(int id);

    void setUnconsumedUserCount(int unconsumedUserCount);

    void setMsg(char *msg);
};


#endif //LMQTT__SERVER_SERVERMESSAGECONTAINER_H
