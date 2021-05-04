cmake_minimum_required(VERSION 3.17)
project(lmqtt__client)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_TOOLCHAIN_FILE /home/vince/programme/vcpkg/scripts/buildsystems/vcpkg.cmake)

# find_path(MAGIC_ENUM_INCLUDE_DIR NAMES magic_enum.hpp PATH_SUFFIXES magic_enum2)
# include_directories(${MAGIC_ENUM_INCLUDE_DIR})

include_directories(../../src/handlers)
include_directories(../../src/handlers/exception)
include_directories(../../src/io)
include_directories(../../src/io/exception)
include_directories(../../src/packets/parsers)
include_directories(../../src/util)
include_directories(../../src/packets)

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

        ../con/ConnectionSession.cpp
        ../con/ConnectionSession.h

        ../packets/factories/exception/PacketCreationException.h
        ../packets/factories/exception/PacketCreationException.cpp
        ../handlers/exception/IllegalSessionStateException.cpp
        ../handlers/exception/IllegalSessionStateException.h
        ../handlers/PacketHandler.cpp
        ../packets/factories/PacketFactory.h
        ../packets/factories/ConnectPacketFactory.cpp
        ../packets/factories/ConnectPacketFactory.h

        ../packets/Payload.cpp ../packets/Payload.h ../packets/parsers/PacketParser.cpp ../handlers/exception/InvalidPacketException.cpp ../handlers/exception/InvalidPacketException.h ../Session.cpp ../Session.h ../packets/factories/ConnectAckPacketFactory.cpp ../packets/factories/ConnectAckPacketFactory.h ../packets/ConnectAckPacket.cpp ../con/ClientConnectionSession.cpp ../con/ClientConnectionSession.h ../handlers/ConnectAckPacketHandler.cpp ../handlers/ConnectAckPacketHandler.h)


#target_include_directories(lmqtt__client PRIVATE
#        ../handlers
#        ../io
#        ../packets
#        ../packet_factories)

