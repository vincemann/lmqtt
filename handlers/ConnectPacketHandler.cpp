//
// Created by vince on 07.04.21.
//


#include "ConnectPacketHandler.h"
#include <stdio.h>
#include "../Session.h"
#include "../ex"

void ConnectPacketHandler::handle(RawPacket *packet) {
    printf("handling connect packet:\n");
    if (g_session->getIoManager().getPacketsReceived().size != 1){

    }
}

