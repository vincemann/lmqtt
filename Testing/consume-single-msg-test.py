from engine import *

start_server()


j = connect(username, password, clientId)
assert j["subscriptions"] == []

# CREATE TOPIC
server_topic_meta_j, servers_topic_msgs_j = publish(topic1, clientId, 0, "init")
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 0
msg = servers_topic_msgs_j[0]
assert msg["id"] == 1
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == "init"


# init msges from publish are removed when first subscriber subscribes
server_topic_meta_j, clients_topic_msgs_j = subscribe(topic1, clientId, 0)
assert server_topic_meta_j["last_msg_id_published"] == 1
assert server_topic_meta_j["subscribed_users_count"] == 1
#
assert clients_topic_msgs_j is None



server_topic_meta_j, servers_topic_msgs_j = publish(topic1, clientId, 0, topic1_msg3)
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 1
#
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg3


j = connect(username, password, clientId)
assert j["subscriptions"] == []


stop_server()