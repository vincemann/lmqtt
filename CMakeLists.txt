cmake_minimum_required(VERSION 3.17)
project(lmqtt__server)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(client)

add_executable(lmqtt__server
        Server.cpp

        packets/RawPacket.h
        packets/RawPacket.cpp
        packets/PacketType.h
        packets/ConnectPacket.h
        packets/ConnectPacket.cpp

        io/PacketIOManager.h
        io/PacketIOManager.cpp
        io/exception/PacketIOException.h
        io/exception/PacketIOException.cpp

        packets/parsers/ConnectPacketParser.h
        packets/parsers/ConnectPacketParser.cpp

        handlers/PacketHandler.h
        handlers/ConnectPacketHandler.h
        handlers/ConnectPacketHandler.cpp

        util/Utils.cpp util/Utils.h Session.cpp Session.h packets/parsers/PacketParser.h packets/parsers/exception/PacketCreationException.cpp packets/parsers/exception/PacketParsingException.h handlers/exception/IllegalSessionStateException.cpp handlers/exception/IllegalSessionStateException.h handlers/PacketHandler.cpp packets/factories/PacketFactory.h packets/factories/ConnectPacketFactory.cpp packets/factories/ConnectPacketFactory.h)

include_directories(lmqtt__server
        handlers
        handlers/exception
        io
        io/exception
        packets/parsers
        util
        packets)


