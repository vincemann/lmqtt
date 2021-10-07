from engine import *

start_server()


connect(username, password, clientId)
connect(username, password, clientId2)
connect(username, password, clientId3)


init_topic(topic1, clientId)
init_topic(topic2, clientId)


# SUBSCRIBE FIRST USER TO FIRST TOPIC
subscribe(topic1, clientId, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1)
assert len(clients_topic_msgs_j) == 0
# SUBSCRIBE FIRST USER TO SECOND TOPIC
subscribe(topic2, clientId, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic2)
assert len(clients_topic_msgs_j) == 0
# SUBSCRIBE SECOND USER TO FIRST TOPIC
subscribe(topic2, clientId2, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId2, topic2)
assert len(clients_topic_msgs_j) == 0



# PULISH FIRST REAL MSG TO FRIST TOPIC
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


# PUBLISH SECOND REAL MSG TO FIRST TOPIC
publish(topic1, clientId2, 0, topic1_msg2)
server_topic_info_j = get_servers_topic_info(topic1)
assert server_topic_info_j["value"] == topic1
assert server_topic_info_j["last_msg_id_published"] == 3
assert server_topic_info_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg2



# PULISH FIRST REAL MSG TO SECOND TOPIC
publish(topic2, clientId2, 0, topic2_msg1)
server_topic_info_j = get_servers_topic_info(topic2)
assert server_topic_info_j["value"] == topic2
assert server_topic_info_j["last_msg_id_published"] == 2
assert server_topic_info_j["subscribed_users_count"] == 2
servers_topic_msgs_j = get_servers_topic_msgs(topic2)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 2
assert msg["value"] == topic2_msg1

# PUBLISH SECOND REAL MSG TO SECOND TOPIC
publish(topic2, clientId2, 0, topic2_msg2)
server_topic_info_j = get_servers_topic_info(topic2)
assert server_topic_info_j["value"] == topic2
assert server_topic_info_j["last_msg_id_published"] == 3
assert server_topic_info_j["subscribed_users_count"] == 2
servers_topic_msgs_j = get_servers_topic_msgs(topic2)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 2
assert msg["value"] == topic2_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 2
assert msg["value"] == topic2_msg2


# CONSUME MSGS client 1, gets all msgs
consume(username, password, clientId)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1)
msg = clients_topic_msgs_j[0]
assert msg["value"] == topic1_msg1
msg = clients_topic_msgs_j[1]
assert msg["value"] == topic1_msg2
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic2)
msg = clients_topic_msgs_j[0]
assert msg["value"] == topic2_msg1
msg = clients_topic_msgs_j[1]
assert msg["value"] == topic2_msg2

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
assert len(servers_topic_msgs_j) == 0

servers_topic_msgs_j = get_servers_topic_msgs(topic2)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic2_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic2_msg2


# CONSUME MSGS client 2, last msgs fully consumed
consume(username, password, clientId2)
clients_topic_msgs_j = get_clients_topic_msgs(clientId2, topic2)
msg = clients_topic_msgs_j[0]
assert msg["value"] == topic2_msg1
msg = clients_topic_msgs_j[1]
assert msg["value"] == topic2_msg2



# msgs are fully consumed, thus deleted
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
assert len(servers_topic_msgs_j) == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic2)
assert len(servers_topic_msgs_j) == 0


stop_server()