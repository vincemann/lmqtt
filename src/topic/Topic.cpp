//
// Created by vince on 14.08.21.
//

#include "Topic.h"

Topic::Topic(long int lastMsgIdPublished, long int subscribedUserCount, char *topic) : _last_msg_id_published(
        lastMsgIdPublished), _subscribed_users_count(subscribedUserCount), value(topic) {}

        long Topic::getLastMsgIdPublished() const {
    return _last_msg_id_published;
}

int Topic::getSubscribedUserCount() const {
    return _subscribed_users_count;
}

char *Topic::getValue() const {
    return value;
}

void Topic::setLastMsgIdPublished(long lastMsgIdPublished) {
    _last_msg_id_published = lastMsgIdPublished;
}

void Topic::setSubscribedUsersCount(int subscribedUsersCount) {
    _subscribed_users_count = subscribedUsersCount;
}

Topic::Topic(char *topic) : value(topic){
    _subscribed_users_count=0;
    // set to one bc first msg is always discarded
    _last_msg_id_published=1;
}

