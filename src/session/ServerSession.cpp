


#include "ServerSession.h"



ServerSession::ServerSession(char *clientId) : _clientId(clientId){
    this->_qos_subscriptions= new std::vector<char *>;
}

std::ostream &operator<<(std::ostream &os, const ServerSession &session) {
    os << "_clientId: " << session._clientId << " _qos_subscriptions: " << session._qos_subscriptions;
    return os;
}

//std::ostream &operator<<(std::ostream &os, const ServerSession &session) {
//    os << "_clientId: " << session._clientId << " _qos_subscriptions: " << session._qos_subscriptions;
//    return os;
//}
