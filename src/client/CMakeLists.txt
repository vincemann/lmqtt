cmake_minimum_required(VERSION 3.17)
project(lmqtt__client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_TOOLCHAIN_FILE
# /home/vince/programme/vcpkg/scripts/buildsystems/vcpkg.cmake)

# find_path(MAGIC_ENUM_INCLUDE_DIR NAMES magic_enum.hpp PATH_SUFFIXES
# magic_enum2) include_directories(${MAGIC_ENUM_INCLUDE_DIR})

include_directories(../con)
include_directories(../files)
include_directories(../handlers)
include_directories(../handlers/exception)
include_directories(../io)
include_directories(../io/exception)
include_directories(../packets)
include_directories(../packets/factories)
include_directories(../packets/factories/exception)
include_directories(../packets/parsers)
include_directories(../packets/parsers/exception)
include_directories(../packets/parsers)
include_directories(../session)
include_directories(../util)

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
        ../packets/parsers/ConnectPacketParser.h
        ../packets/parsers/ConnectPacketParser.cpp
        ../handlers/PacketHandler.h
        ../handlers/ConnectPacketHandler.h
        ../handlers/ConnectPacketHandler.cpp
        ../util/Utils.cpp
        ../util/Utils.h
        ../packets/parsers/PacketParser.h
        ../packets/parsers/exception/PacketParsingException.cpp
        ../packets/parsers/exception/PacketParsingException.h
        ../packets/parsers/ConnAckPacketParser.h
        ../packets/parsers/ConnAckPacketParser.cpp
        ../con/Connection.cpp
        ../con/Connection.h
        ../packets/factories/exception/PacketCreationException.h
        ../packets/factories/exception/PacketCreationException.cpp
        ../handlers/exception/IllegalSessionStateException.cpp
        ../handlers/exception/IllegalSessionStateException.h
        ../handlers/PacketHandler.cpp
        ../packets/factories/PacketFactory.h
        ../packets/factories/ConnectPacketFactory.cpp
        ../packets/factories/ConnectPacketFactory.h
        ../packets/Payload.cpp
        ../packets/Payload.h
        ../packets/parsers/PacketParser.cpp
        ../handlers/exception/InvalidPacketException.cpp
        ../handlers/exception/InvalidPacketException.h
        ../packets/factories/ConnectAckPacketFactory.cpp
        ../packets/factories/ConnectAckPacketFactory.h
        ../packets/ConnectAckPacket.cpp
        ../con/ClientConnection.cpp
        ../con/ClientConnection.h
        ../handlers/ConnectAckPacketHandler.cpp
        ../handlers/ConnectAckPacketHandler.h
        ../files/FileDataManager.h
        ../files/FileDataManager.cpp
        ../session/ServerSession.h
        ../session/ServerSession.cpp
        ../session/ServerSessionRepository.h
        ../session/ServerSessionRepository.cpp
        ../MsgException.cpp ../MsgException.h ../session/ClientSession.cpp ../session/ClientSession.h ../session/ClientSessionRepository.cpp ../session/ClientSessionRepository.h)

# target_include_directories(lmqtt__client PRIVATE ../handlers ../io ../packets
# ../packet_factories)
