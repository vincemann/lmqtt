from pwn import *
import json
import threading
import time

username = "gil"
username2 = "vincemann"
password = "pass123"
lmqtt_path = "/home/vince/.lmqtt"
clientId = "gilsClientId"
clientId2 = "vincemannsClientId"
clientId3 = "gülClientId"

topic_init_msg = "init"
topic1 = "jeffseid"
topic2 = "jeff-bezos"
topic1_msg1 = "my name is jeff"
topic2_msg1 = "my name is bezos jeff"
topic1_msg2 = "my name is not jeff anymore"
topic2_msg2 = "my name is not bezos jeff anymore"
topic1_msg3 = "my name is gil"
topic1_msg4 = "my name is vincemann"
client_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/src/client/lmqtt__client"
server_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/lmqtt__server"
DONE = False


def run_server(no_publish_ack_count=0, no_publish_ack_start=0):
    global DONE
    io = process([server_binary, "--no-publish-ack-count="+str(no_publish_ack_count), "--no-publish-ack-start="+str(no_publish_ack_start), ])
    while True:
        server_output = io.recv(timeout=2).decode("utf-8")
        log.warn(f"server_output: {server_output}")
        if DONE:
            break


def start_server(no_publish_ack_count=0, no_publish_ack_start=0, rm=True):
    if rm:
        process(["rm", "-rf", lmqtt_path]).recvall()
    server_thread = threading.Thread(target=run_server, args=(no_publish_ack_count, no_publish_ack_start,))
    server_thread.start()

    time.sleep(1.5)


def readf(path):
    return read(path).decode("utf-8")


def stop_server():
    global DONE
    DONE = True
    # time.sleep(2.5)


def connect(username, password, clientId):
    r = process(client_binary + " connect --user "+username+" --password "+password+" --id "+clientId+" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)


def consume(username, password, clientId):
    r = process(client_binary + " connect --user "+username+" --password "+password+" --id "+clientId+" --consume-messages 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    time.sleep(0.5)
    log.info(r)


def publish(topic, clientId, qos, msg):
    r = process(client_binary + " publish --topic "+topic+" --id " + clientId + " --qos " + str(qos) + " \"" + msg + "\" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    time.sleep(0.5)
    log.info(r)


def publish_no_ack(topic, clientId, qos, msg):
    r = process(client_binary + " publish --topic "+topic+" --id " + clientId + " --qos " + str(qos) + " \"" + msg + "\" 127.0.0.1 8080", shell=True).recvall(timeout=3).decode("utf-8")
    time.sleep(0.5)
    log.info(r)


def init_topic(topic, clientId):
    publish(topic, clientId, 0, topic_init_msg)
    servers_topic_msgs_j = get_servers_topic_msgs(topic)
    assert len(servers_topic_msgs_j) == 0
    server_topic_meta_j = get_servers_topic_info(topic)
    assert server_topic_meta_j["value"] == topic
    assert server_topic_meta_j["last_msg_id_published"] == 1
    assert server_topic_meta_j["subscribed_users_count"] == 0


def subscribe(topic, clientId, qos):
    r = process(client_binary + " subscribe --topic "+topic+" --id " + clientId + " --qos " + str(qos) + " 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    time.sleep(0.5)
    log.info(r)


def unsubscribe(topic, clientId):
    r = process(client_binary + " unsubscribe --topic "+topic+" --id " + clientId + " 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    time.sleep(0.5)
    log.info(r)

# HELPERS


def get_servers_topic_msgs(topic):
    servers_topic_msgs = readf(lmqtt_path + "/server/topics/" + topic + "/messages")
    return json.loads(servers_topic_msgs)


def get_clients_topic_msgs(clientId, topic):
    clients_topic_msgs = readf(lmqtt_path + "/client/" + clientId + "/topics/" + topic + "/messages")
    return json.loads(clients_topic_msgs)

# def assert_no_clients_topic():


def get_clients_retransmission_msgs(clientId):
    clients_topic_msgs = readf(lmqtt_path + "/client/" + clientId + "/retransmit/messages")
    return json.loads(clients_topic_msgs)


def get_servers_topic_info(topic):
    servers_topic_info = readf(lmqtt_path + "/server/topics/" + topic + "/topic")
    return json.loads(servers_topic_info)


def get_clients_client_info(clientId):
    clients_client_info = readf(lmqtt_path + "/client/info/"+clientId)
    return json.loads(clients_client_info)


def get_servers_client_info(clientId):
    servers_client_info = readf(lmqtt_path + "/server/client-info/"+clientId)
    return json.loads(servers_client_info)