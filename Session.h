//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_SESSION_H
#define LMQTT__SERVER_SESSION_H

#include "io/PacketIOManager.h"

extern Session *g_session;

class Session {
    PacketIOManager& io_manager;
public:
    Session(PacketIOManager &ioManager);
    PacketIOManager &getIoManager() const;
};


#endif //LMQTT__SERVER_SESSION_H
