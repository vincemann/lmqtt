//
// Created by vince on 14.08.21.
//

#ifndef LMQTT__SERVER_TOPIC_H
#define LMQTT__SERVER_TOPIC_H


class Topic {


public:
    long int _last_msg_id_published;
    long int _subscribed_users_count;
    char *value;
    Topic(long int lastMsgIdPublished, long int subscribedUserCount, char *topic);
    Topic(char* topic);

    long getLastMsgIdPublished() const;

    int getSubscribedUserCount() const;

    char *getValue() const;

    void setLastMsgIdPublished(long lastMsgIdPublished);

    void setSubscribedUsersCount(int subscribedUsersCount);


};


#endif //LMQTT__SERVER_TOPIC_H
