from engine import *

start_server()

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


publish(topic1, clientId, 0, topic1_msg2)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[1]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2


stop_server()