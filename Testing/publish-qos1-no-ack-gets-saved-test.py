from engine import *

start_server(no_publish_ack_start=1, no_publish_ack_count=1)

connect(username, password, clientId)

init_topic(topic1, clientId)

publish_no_ack(topic1, clientId, 1, topic1_msg1)

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
assert len(servers_topic_msgs_j) == 0
clients_retransmit_msgs = get_clients_retransmission_msgs(clientId)
msg = clients_retransmit_msgs[0]
assert msg["value"] == topic1_msg1
assert len(clients_retransmit_msgs) == 1


start_server(no_publish_ack_start=0, no_publish_ack_count=1, rm=False)

publish_no_ack(topic1, clientId, 1, topic1_msg2)

servers_topic_msgs_j = get_servers_topic_msgs(topic1)
assert len(servers_topic_msgs_j) == 0
clients_retransmit_msgs = get_clients_retransmission_msgs(clientId)
msg = clients_retransmit_msgs[0]
assert msg["value"] == topic1_msg1
msg = clients_retransmit_msgs[1]
assert msg["value"] == topic1_msg2
assert len(clients_retransmit_msgs) == 2



stop_server()