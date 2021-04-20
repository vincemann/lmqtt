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

        ../io/PacketIOManager.h
        ../io/PacketIOManager.cpp
        ../io/exception/PacketIOException.h
        ../io/exception/PacketIOException.cpp

        ../io/parsers/ConnectPacketParser.h
        ../io/parsers/ConnectPacketParser.cpp

        ../handlers/PacketHandler.h
        ../handlers/ConnectPacketHandler.h
        ../handlers/ConnectPacketHandler.cpp

        ../util/Utils.cpp ../util/Utils.h ../io/parsers/PacketParser.h ../io/exception/PacketParsingException.cpp ../io/exception/PacketParsingException.h ../handlers/exception/IllegalSessionStateException.cpp ../handlers/exception/IllegalSessionStateException.h ../io/parsers/PacketParser.cpp)

target_include_directories(lmqtt__client PRIVATE
        ../handlers
        ../io
        ../packets
        ../packet_factories)
