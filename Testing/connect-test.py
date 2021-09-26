from engine import *

start_server()


j = connect(username, password, clientId)
assert j["subscriptions"] == []



stop_server()