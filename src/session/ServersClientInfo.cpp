


#include "ServersClientInfo.h"



ServersClientInfo::ServersClientInfo(char *clientId) : _clientId(clientId){
    this->subscriptions= new std::vector<char *>;
}

std::ostream &operator<<(std::ostream &os, const ServersClientInfo &session) {
    os << "_clientId: " << session._clientId << " subscriptions: " << session.subscriptions;
    return os;
}

//std::ostream &operator<<(std::ostream &os, const ServerSession &session) {
//    os << "_clientId: " << session._clientId << " subscriptions: " << session.subscriptions;
//    return os;
//}
