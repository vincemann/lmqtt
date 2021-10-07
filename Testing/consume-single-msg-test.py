from engine import *

start_server()


connect(username, password, clientId)
connect(username, password, clientId2)


init_topic(topic1, clientId)


# SUBSCRIBE FIRST USER
subscribe(topic1, clientId, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1)
assert len(clients_topic_msgs_j) == 0


publish(topic1, clientId2, 0, topic1_msg1)
server_topic_info_j = get_servers_topic_info(topic1)
assert server_topic_info_j["value"] == topic1
assert server_topic_info_j["last_msg_id_published"] == 2
assert server_topic_info_j["subscribed_users_count"] == 1
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
assert len(servers_topic_msgs_j) == 0


stop_server()