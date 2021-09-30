from engine import *

start_server()


connect(username, password, clientId)
connect(username, password, clientId2)


# CREATE TOPIC
publish(topic1, clientId, 0, "init")
# should create topic by publishing msg
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 1
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == "init"


# init msges from publish are removed when first subscriber subscribes
subscribe(topic1, clientId, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1, empty=True)
#
assert clients_topic_msgs_j is None


publish(topic1, clientId2, 0, topic1_msg1)
# should create topic by publishing msg
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1


consume(username, password, clientId)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1)
msg = clients_topic_msgs_j[0]
assert msg["value"] == topic1_msg1

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
assert servers_topic_msgs_j == []


stop_server()