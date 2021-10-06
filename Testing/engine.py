from pwn import *
import json
import threading
import time

username = "gil"
password = "pass123"
lmqtt_path = "/home/vince/.lmqtt"
clientId = "gilsClientId"
clientId2 = "vincemannsClientId"
clientId3 = "gülClientId"

topic_init_msg = "init"
topic1 = "jeffseid"
topic1_msg1 = "my name is jeff"
topic1_msg2 = "my name is not jeff anymore"
topic1_msg3 = "my name is gil"
topic1_msg4 = "my name is vincemann"
client_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/src/client/lmqtt__client"
server_binary = "/home/vince/projekte/important/mqtt/lmqtt+-server/lmqtt__server"
DONE = False


def run_server():
    global DONE
    io = process([server_binary])
    while True:
        server_output = io.recv(timeout=2).decode("utf-8")
        log.warn(f"server_output: {server_output}")
        if DONE:
            break


def start_server():
    process(["rm", "-rf", lmqtt_path]).recvall()
    server_thread = threading.Thread(target=run_server)
    server_thread.start()

    time.sleep(1.5)


def readf(path):
    return read(path).decode("utf-8")


def stop_server():
    global DONE
    DONE = True


def connect(username, password, clientId):
    r = process(client_binary + " connect -u "+username+" -p "+password+" -i "+clientId+" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)


def consume(username, password, clientId):
    r = process(client_binary + " connect -u "+username+" -p "+password+" -i "+clientId+" -m 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)


def publish(topic, clientId, qos, msg):
    r = process(client_binary + " publish -t "+topic+" -i " + clientId + " -q " + str(qos) + " \"" + msg + "\" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)


def init_topic(topic, clientId):
    r = process(client_binary + " publish -t "+topic+" -i " + clientId + " -q " + str(0) + " \"" + topic_init_msg + "\" 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)
    servers_topic_msgs_j = get_servers_topic_msgs(topic1)
    assert len(servers_topic_msgs_j) == 0
    server_topic_meta_j = get_servers_topic_info(topic)
    assert server_topic_meta_j["value"] == topic
    assert server_topic_meta_j["last_msg_id_published"] == 1
    assert server_topic_meta_j["subscribed_users_count"] == 0


def subscribe(topic, clientId, qos):
    r = process(client_binary + " subscribe -t "+topic+" -i " + clientId + " -q " + str(qos) + " 127.0.0.1 8080", shell=True).recvall().decode("utf-8")
    log.info(r)


# HELPERS


def get_servers_topic_msgs(topic):
    servers_topic_msgs = readf(lmqtt_path + "/server/topics/" + topic + "/messages")
    return json.loads(servers_topic_msgs)


def get_clients_topic_msgs(clientId, topic):
    clients_topic_msgs = readf(lmqtt_path + "/client/" + clientId + "/topics/" + topic + "/messages")
    # if not empty:
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