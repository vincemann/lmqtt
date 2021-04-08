cmake_minimum_required(VERSION 3.17)
project(lmqtt__client)

set(CMAKE_CXX_STANDARD 17)


add_executable(lmqtt__client
        Client.cpp

        ../packets/RawPacket.h
        ../packets/RawPacket.cpp
        ../packets/PacketType.h
        ../packets/ConnectPacket.h
        ../packets/ConnectPacket.cpp

        ../parser/PacketReceiver.h
        ../parser/PacketReceiver.cpp
        ../parser/PacketParsingException.h
        ../parser/PacketParsingException.cpp

        ../parser/factories/ConnectPacketFactory.h
        ../parser/factories/ConnectPacketFactory.cpp

        ../packet_handlers/PacketHandler.h
        ../packet_handlers/ConnectPacketHandler.h
        ../packet_handlers/ConnectPacketHandler.cpp

        ../parser/PacketSender.cpp ../parser/PacketSender.h ../util/Utils.cpp ../util/Utils.h)

target_include_directories(lmqtt__client PRIVATE
        ../packet_handlers
        ../parser
        ../packets
        ../packet_factories)
