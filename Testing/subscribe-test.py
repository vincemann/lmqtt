from engine import *

# start_server()



connect(username, password, clientId)




publish(topic1, clientId, 0, topic1_msg1)
# should create topic by publishing msg
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 1
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1



# init msges from publish are removed when first subscriber subscribes
subscribe(topic1, clientId, 0)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 1
#
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1, empty=True)
assert clients_topic_msgs_j is None




publish(topic1, clientId, 0, topic1_msg2)
# should create topic by publishing msg
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg2



publish(topic1, clientId, 0, topic1_msg3)
# should create topic by publishing msg
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 3
assert server_topic_meta_j["subscribed_users_count"] == 1

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg2
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg3


# NEED TO INIT CONNECT BEFORE SUBSCRIBING IS POSSIBLE
connect("vincemann", password, clientId2)

# init msges from publish are removed when first subscriber subscribes
subscribe(topic1, clientId2, 0)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 3
assert server_topic_meta_j["subscribed_users_count"] == 2
#
clients_topic_msgs_j = get_clients_topic_msgs(clientId2, topic1, empty=True)
assert clients_topic_msgs_j is None

stop_server()


# # client side
# clients_topic_msgs_j = get_clients_topic_msgs(topic, empty=fresh)
#
# # checking server side
# server_topic_meta_j = get_servers_topic_info(topic)
# assert server_topic_meta_j["value"] == topic
#
# return server_topic_meta_j, clients_topic_msgs_j