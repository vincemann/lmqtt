cmake_minimum_required(VERSION 3.17)
project(lmqtt__server)

set(CMAKE_CXX_STANDARD 17)


add_executable(lmqtt__server Main.cpp packets/RawPacket.h PacketType.h packet_handlers/ConnectPacketHandler.h packet_handlers/PacketHandler.h packets/ConnectPacket.h parser/PacketParser.cpp parser/PacketParser.h parser/ParserException.cpp parser/ParserException.h packet_factories/ConnectPacketFactory.cpp packet_factories/ConnectPacketFactory.h packets/RawPacket.cpp packets/ConnectPacket.cpp)

target_include_directories(lmqtt__server PRIVATE packet_handlers parser packets packet_factories)
