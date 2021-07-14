//
// Created by vince on 14.07.21.
//

#include "DisconnectPacket.h"


DisconnectPacket::DisconnectPacket() : RawPacket(0, 0, 0, PacketType::DISCONNECT) {

}

DisconnectPacket::DisconnectPacket(RawPacket *rawPacket) : RawPacket(rawPacket) {}
