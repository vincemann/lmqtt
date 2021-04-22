//
// Created by vince on 07.04.21.
//


#include <stdio.h>

#include "ConnectPacketHandler.h"
#include "../Session.h"
#include "exception/IllegalSessionStateException.h"
#include "../packets/RawPacket.h"

ConnectPacketHandler::ConnectPacketHandler(Session &session) : PacketHandler(session) {}

void ConnectPacketHandler::handle(RawPacket *packet) {
    printf("handling connect packet:\n");
    if (_session.getPacketsReceived().size != 1){
        throw new IllegalSessionStateException("received more than one Connect Packet");
    }


}

