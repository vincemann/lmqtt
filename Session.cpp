//
// Created by vince on 08.04.21.
//

#include "Session.h"


Session *g_session = 0;

Session::Session(PacketIOManager &ioManager) : io_manager(ioManager) {}

PacketIOManager &Session::getIoManager() const {
    return io_manager;
}
