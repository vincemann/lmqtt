from engine import *

start_server(no_publish_ack_start=2, no_publish_ack_count=1)

connect(username, password, clientId)

init_topic(topic1, clientId)

publish(topic1, clientId, 0, topic1_msg1)
#
server_topic_meta_j = get_servers_topic_info(topic1)
assert server_topic_meta_j["value"] == topic1
assert server_topic_meta_j["last_msg_id_published"] == 2
assert server_topic_meta_j["subscribed_users_count"] == 0
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1

# wont be acked and handled but still has qos1
publish_no_ack(topic1, clientId, 1, topic1_msg2)
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1
assert len(servers_topic_msgs_j) == 1


# client stores qos 1 msg for retransmission
clients_retransmit_msgs = get_clients_retransmission_msgs(clientId)
msg = clients_retransmit_msgs[0]
assert msg["value"] == topic1_msg2
assert len(clients_retransmit_msgs) == 1

# server works again
start_server(rm=False)


connect(username, password, clientId)
# msg is resend and now successfully acked -> server has it
servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2
assert len(servers_topic_msgs_j) == 2

# client has removed qos1 msg from retransmission folder
clients_retransmit_msgs = get_clients_retransmission_msgs(clientId)
assert len(clients_retransmit_msgs) == 0


# publish again without issues
publish(topic1, clientId, 1, topic1_msg3)

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
msg = servers_topic_msgs_j[0]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1
msg = servers_topic_msgs_j[1]
assert msg["id"] == 3
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2
msg = servers_topic_msgs_j[2]
assert msg["id"] == 4
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg3
assert len(servers_topic_msgs_j) == 3

# client has removed qos1 msg from retransmission folder
clients_retransmit_msgs = get_clients_retransmission_msgs(clientId)
assert len(clients_retransmit_msgs) == 0


stop_server()