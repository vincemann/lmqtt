from engine import *

start_server()


connect(username, password, clientId)

init_topic(topic1, clientId)


publish(topic1, clientId, 0, topic1_msg2)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2


subscribe(topic1, clientId, 0)
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
#
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1)
assert len(clients_topic_msgs_j) == 0


# msges from publish are still there
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2





stop_server()