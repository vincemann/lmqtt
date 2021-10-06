from engine import *

start_server()


connect(username, password, clientId)
connect(username, password, clientId2)
connect(username, password, clientId3)


# CREATE TOPIC / PUBLISH INIT MSG
log.info("INIT TOPIC PUBLISH")
publish(topic1, clientId, 0, "init")
# should create topic by publishing msg
server_topic_info_j = get_servers_topic_info(topic1)
assert server_topic_info_j["value"] == topic1
assert server_topic_info_j["last_msg_id_published"] == 1
assert server_topic_info_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 1
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == "init"


# SUBSCRIBE FIRST USER
# init msges from publish are removed when first subscriber subscribes
log.info("FIRST SUB")
subscribe(topic1, clientId, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId, topic1, empty=True)
#
assert clients_topic_msgs_j is None


# PULISH FIRST REAL MSG
log.info("FIRST PUB WITH REAL MSG")
publish(topic1, clientId2, 0, topic1_msg1)
# should create topic by publishing msg
server_topic_info_j = get_servers_topic_info(topic1)
assert server_topic_info_j["value"] == topic1
assert server_topic_info_j["last_msg_id_published"] == 2
assert server_topic_info_j["subscribed_users_count"] == 1
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1

# SUBSCRIBE SECOND USER
# todo this subscribe deletes second publish msg on publish below
log.info("SECOND SUB")
subscribe(topic1, clientId2, 0)
clients_topic_msgs_j = get_clients_topic_msgs(clientId2, topic1, empty=True)

assert clients_topic_msgs_j is None

# PUBLISH SECOND REAL MSG
log.info("SECOND PUBLISH WITH REAL MSG")
publish(topic1, clientId2, 0, topic1_msg2)
# should create topic by publishing msg
server_topic_info_j = get_servers_topic_info(topic1)
assert server_topic_info_j["value"] == topic1
assert server_topic_info_j["last_msg_id_published"] == 3
assert server_topic_info_j["subscribed_users_count"] == 2
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 1
assert msg["value"] == topic1_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 2
assert msg["value"] == topic1_msg2


stop_server()