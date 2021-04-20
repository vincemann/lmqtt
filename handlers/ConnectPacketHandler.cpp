//
// Created by vince on 07.04.21.
//


#include "ConnectPacketHandler.h"
#include <stdio.h>
#include "../Session.h"
#include "exception/IllegalSessionStateException.h"

void ConnectPacketHandler::handle(RawPacket *packet) {
    printf("handling connect packet:\n");
    if (g_session->getIoManager().getPacketsReceived().size != 1){
        throw new IllegalSessionStateException("received more than one Connect Packet");
    }


}

