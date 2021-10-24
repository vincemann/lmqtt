


#include "ServersClientInfo.h"



ServersClientInfo::ServersClientInfo(char *clientId) : _clientId(clientId){
    this->subscriptions= new std::vector<Subscription*>;
}

std::ostream &operator<<(std::ostream &os, const ServersClientInfo &session) {
    os << "_clientId: " << session._clientId << " subscriptions: " << session.subscriptions;
    return os;
}

char *ServersClientInfo::getClientId() const {
    return _clientId;
}

std::vector<Subscription *> *ServersClientInfo::getSubscriptions() const {
    return subscriptions;
}

//std::ostream &operator<<(std::ostream &os, const ServerSession &session) {
//    os << "_clientId: " << session._clientId << " subscriptions: " << session.subscriptions;
//    return os;
//}
