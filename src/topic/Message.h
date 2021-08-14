//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_MESSAGE_H
#define LMQTT__SERVER_MESSAGE_H


class Message {
    long _id;
    int _unconsumed_user_count;
    char* _msg;
public:
    Message(long id, int unconsumedUserCount, char *msg);
    Message(char *msg);

    long getId() const;

    int getUnconsumedUserCount() const;

    char *getMsg() const;
};


#endif //LMQTT__SERVER_MESSAGE_H
