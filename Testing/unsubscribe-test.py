from engine import *

start_server()


connect(username, password, clientId)


init_topic(topic1, clientId)


subscribe(topic1, clientId, 0)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 1


publish(topic1, clientId, 0, topic1_msg1)
#
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1
assert len(servers_topic_msgs_j) == 1


# NEED TO INIT CONNECT BEFORE SUBSCRIBING IS POSSIBLE
connect(username2, password, clientId2)

# SUBSCRIBE SECOND USER
subscribe(topic1, clientId2, 0)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 2


publish(topic1, clientId, 0, topic1_msg2)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 3
assert server_topic_meta_j["subscribed_users_count"] == 2
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 2
assert msg["value"] == topic1_msg2
assert len(servers_topic_msgs_j) == 2


# UNSUB FIRST USER -> FIRST MSG DELETED
unsubscribe(topic1, clientId)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 3
assert server_topic_meta_j["subscribed_users_count"] == 1


servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg2
assert len(servers_topic_msgs_j) == 1


stop_server()


# # client side
# clients_topic_msgs_j = get_clients_topic_msgs(topic, empty=fresh)
#
# # checking server side
# server_topic_meta_j = get_servers_topic_info(topic)
# assert server_topic_meta_j["value"] == topic
#
# return server_topic_meta_j, clients_topic_msgs_j