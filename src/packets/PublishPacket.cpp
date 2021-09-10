//
// Created by vince on 10.09.21.
//

#include "PublishPacket.h"

PublishPacket::PublishPacket(RawPacket *rawPacket, unsigned char dupFlag, unsigned short qos, unsigned char retainFlag,
                             char *topic, unsigned short packetId, char *msg) : RawPacket(rawPacket), dupFlag(dupFlag),
                                                                                qos(qos), retainFlag(retainFlag),
                                                                                topic(topic), packetId(packetId),
                                                                                msg(msg) {}
