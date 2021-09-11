cmake_minimum_required(VERSION 3.17)
project(lmqtt__server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
# set(nlohmann_json_DIR includes)
# set (CMAKE_CXX_STANDARD 11)

add_subdirectory(src/client)

include_directories(./src/con)
include_directories(./src/files)
include_directories(./src/handlers)
include_directories(./src/handlers/exception)
include_directories(./src/io)
include_directories(./src/io/exception)
include_directories(./src/packets)
include_directories(./src/packets/factories)
include_directories(./src/packets/factories/exception)
include_directories(./src/packets/parsers)
include_directories(./src/packets/parsers/exception)
include_directories(./src/packets/parsers)
include_directories(./src/session)
include_directories(./src/util)

#include_directories(lmqtt__server)
# include_directories(./single_include/nlohmann)

# find_package(jsoncpp CONFIG REQUIRED)
# target_link_libraries(main PRIVATE jsoncpp_object jsoncpp_static)

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
        src/util/Utils.cpp
        src/util/Utils.h
        src/con/Connection.cpp
        src/con/Connection.h
        src/packets/parsers/PacketParser.h
        src/packets/parsers/exception/PacketParsingException.cpp
        src/packets/parsers/exception/PacketParsingException.h
        src/handlers/exception/IllegalSessionStateException.cpp
        src/handlers/exception/IllegalSessionStateException.h
        src/handlers/PacketHandler.cpp
        src/packets/factories/PacketFactory.h
        src/packets/factories/ConnectPacketFactory.cpp
        src/packets/factories/ConnectPacketFactory.h
        src/packets/Payload.cpp
        src/packets/Payload.h
        src/packets/parsers/PacketParser.cpp
        src/handlers/exception/InvalidPacketException.cpp
        src/handlers/exception/InvalidPacketException.h
        src/session/ServersClientInfo.cpp
        src/session/ServersClientInfo.h
        src/packets/ConnectAckPacket.h
        src/packets/factories/ConnectAckPacketFactory.cpp
        src/packets/factories/ConnectAckPacketFactory.h
        src/packets/ConnectAckPacket.cpp
        src/con/ServerConnection.cpp
        src/con/ServerConnection.h
        src/session/ServersClientInfoRepository.h
        src/session/ServersClientInfoRepository.cpp
        src/json.hpp
        src/files/FileDataManager.h
        src/files/FileDataManager.cpp
        src/MsgException.cpp
        src/MsgException.h
        src/ServerConnectionManager.cpp
        src/ServerConnectionManager.h
        src/packets/DisconnectPacket.cpp
        src/packets/DisconnectPacket.h
        src/packets/parsers/DisconnectPacketParser.cpp
        src/packets/parsers/DisconnectPacketParser.h
        src/handlers/DisconnectPacketHandler.cpp
        src/handlers/DisconnectPacketHandler.h
        src/packets/parsers/SubscribePacketParser.h
        src/packets/parsers/SubscribePacketParser.cpp
        src/packets/SubscribePacket.h
        src/packets/SubscribePacket.cpp
        src/handlers/SubscribePacketHandler.cpp
        src/handlers/SubscribePacketHandler.h
        src/packets/SubscribeAckPacket.cpp
        src/packets/SubscribeAckPacket.h
        src/packets/factories/SubAckPacketFactory.cpp
        src/packets/factories/SubAckPacketFactory.h
        src/topic/ServerTopicRepository.cpp
        src/topic/ServerTopicRepository.h
        src/topic/Topic.cpp
        src/topic/Topic.h
        src/topic/Message.cpp
        src/topic/Message.h
        src/packets/factories/PublishPacketFactory.cpp src/packets/factories/PublishPacketFactory.h src/packets/PublishPacket.cpp src/packets/PublishPacket.h src/packets/parsers/PublishPacketParser.cpp src/packets/parsers/PublishPacketParser.h src/handlers/ServerPublishPacketHandler.cpp src/handlers/ServerPublishPacketHandler.h src/Subscription.cpp src/Subscription.h)


# find_package(nlohmann_json CONFIG REQUIRED)
# target_link_libraries(lmqtt__server PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
