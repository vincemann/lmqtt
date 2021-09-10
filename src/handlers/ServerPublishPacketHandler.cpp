//
// Created by vince on 10.09.21.
//

#include <PublishPacket.h>
#include "ServerPublishPacketHandler.h"

void ServerPublishPacketHandler::handle(RawPacket *packet) {
    PublishPacket* publishPacket = static_cast<PublishPacket*>(packet);

}
