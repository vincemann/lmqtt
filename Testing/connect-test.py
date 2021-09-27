from engine import *

start_server()


connect(username, password, clientId)
# checking client side
clients_client_info_j = get_clients_client_info(clientId)
assert clients_client_info_j["clientId"] == clientId
assert clients_client_info_j["password"] == password
assert clients_client_info_j["username"] == username
# checking server side
server_client_info_j = get_servers_client_info(clientId)
assert server_client_info_j["clientId"] == clientId
assert server_client_info_j["subscriptions"] == []


stop_server()