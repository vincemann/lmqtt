cmake_minimum_required(VERSION 3.17)
project(lmqtt__server)

set(CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_STANDARD 11)

add_subdirectory(src/client)

include_directories(./src/handlers)
include_directories(./src/handlers/exception)
include_directories(./src/io)
include_directories(./src/io/exception)
include_directories(./src/packets/parsers)
include_directories(./src/util)
include_directories(./src/packets)
include_directories(lmqtt__server)

add_executable(lmqtt__server
        src/Server.cpp

        src/packets/RawPacket.h
        src/packets/RawPacket.cpp
        src/packets/PacketType.h
        src/packets/ConnectPacket.h
        src/packets/ConnectPacket.cpp

        src/io/PacketIOManager.h
        src/io/PacketIOManager.cpp
        src/io/exception/PacketIOException.h
        src/io/exception/PacketIOException.cpp

        src/packets/factories/exception/PacketCreationException.h
        src/packets/factories/exception/PacketCreationException.cpp

        src/packets/parsers/ConnectPacketParser.h
        src/packets/parsers/ConnectPacketParser.cpp

        src/handlers/PacketHandler.h
        src/handlers/ConnectPacketHandler.h
        src/handlers/ConnectPacketHandler.cpp

        src/util/Utils.cpp src/util/Utils.h
        src/Session.cpp
        src/Session.h
        src/packets/parsers/PacketParser.h
        src/packets/parsers/exception/PacketParsingException.cpp

        src/packets/parsers/exception/PacketParsingException.h
        src/handlers/exception/IllegalSessionStateException.cpp
        src/handlers/exception/IllegalSessionStateException.h
        src/handlers/PacketHandler.cpp src/packets/factories/PacketFactory.h
        src/packets/factories/ConnectPacketFactory.cpp
        src/packets/factories/ConnectPacketFactory.h src/packets/Payload.cpp src/packets/Payload.h)




