from engine import *

start_server()


connect(username, password, clientId)


init_topic(topic1, clientId)


# init msges from publish are removed when first subscriber subscribes
subscribe(topic1, clientId, 0)
servers_topic_info_j = get_servers_topic_info(topic1)
assert servers_topic_info_j["last_msg_id_published"] == 1
assert servers_topic_info_j["subscribed_users_count"] == 1


publish(topic1, clientId, 0, topic1_msg3)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg3


publish(topic1, clientId, 0, topic1_msg4)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 3
assert server_topic_meta_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg3
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg4


stop_server()