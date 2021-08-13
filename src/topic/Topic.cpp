//
// Created by vince on 14.08.21.
//

#include "Topic.h"

Topic::Topic(long lastMsgIdPublished, int subscribedUserCount, char *topic) : _last_msg_id_published(
        lastMsgIdPublished), _subscribed_user_count(subscribedUserCount), _topic(topic) {}

long Topic::getLastMsgIdPublished() const {
    return _last_msg_id_published;
}

int Topic::getSubscribedUserCount() const {
    return _subscribed_user_count;
}

char *Topic::getTopic() const {
    return _topic;
}
