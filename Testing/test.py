from pwn import *
import json

username= "gil"
password = "pass123"
lmqtt_path = "/home/vince/.lmqtt"
clientId = "gilsClientId"
topic1 = "jeffseid"
topic1_msg1 = "my name is jeff"
topic1_msg2 = "my name is not jeff anymore"
client_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/src/client/lmqtt__client"
server_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/lmqtt__server"


def readp(path):
    return read(path).decode("utf-8")

def connect(username, password, clientId):
    r = process(client_binary + " connect -u "+username+" -p "+password+" -i "+clientId+" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)
    # checking client side
    clients_client_info = readp(lmqtt_path+"/client/info/gilsClientId")
    j = json.loads(clients_client_info)
    assert j["clientId"] == clientId
    assert j["password"] == password
    assert j["username"] == username
    # checking server side
    servers_client_info = readp(lmqtt_path+"/server/client-info/gilsClientId")
    j = json.loads(servers_client_info)
    assert j["clientId"] == clientId
    return j


def subscribe(topic, clientId, qos):
    r = process(client_binary + " subscribe -t "+topic+" -i " + clientId + " -q " + str(qos) + " 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)
    # checking client side
    servers_topic_info = readp(lmqtt_path+"/server/topics/"+topic1+"/topic")
    topic_j = json.loads(servers_topic_info)
    assert topic_j["value"] == topic

    servers_topic_msgs = readp(lmqtt_path+"/server/topics/"+topic1+"/messages")
    msgs_j = json.loads(servers_topic_msgs)

    return topic_j, msgs_j





j = connect(username, password, clientId)
assert j["subscriptions"] == []


def publish(topic, clientId, qos, msg):
    r = process(client_binary + " publish -t "+topic+" -i " + clientId + " -q " + str(qos) + " \""+msg+"\" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    # should create topic by publishing msg
    log.info(r)
    servers_topic_info = readp(lmqtt_path+"/server/topics/"+topic1+"/topic")
    topic_j = json.loads(servers_topic_info)
    assert topic_j["value"] == topic

    servers_topic_msgs = readp(lmqtt_path+"/server/topics/"+topic1+"/messages")
    assert msg in servers_topic_msgs
    msgs_j = json.loads(servers_topic_msgs)

    return topic_j, msgs_j


topic_j, msgs_j = publish(topic1, clientId, 0, topic1_msg1)
assert topic_j["last_msg_id_published"] == 1
assert topic_j["subscribed_users_count"] == 0
msg = msgs_j[0]
assert msg["id"] == 1
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg1

topic_j, msgs_j = publish(topic1, clientId, 0, topic1_msg2)
assert topic_j["last_msg_id_published"] == 2
assert topic_j["subscribed_users_count"] == 0
msg = msgs_j[1]
assert msg["id"] == 2
assert msg["unconsumed_user_count"] == 0
assert msg["value"] == topic1_msg2


# init msges from publish are removed when first subscriber subscribes
topic_j, msgs_j = subscribe(topic1, clientId, 0)
assert topic_j["last_msg_id_published"] == 2
assert topic_j["subscribed_users_count"] == 1
assert msgs_j == []



# process(["rm", "-rf", lmqtt_path]).recvall()




