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
        ../session/ServersClientInfo.h
        ../session/ServersClientInfo.cpp
        ../session/ServersClientInfoRepository.h
        ../session/ServersClientInfoRepository.cpp
        ../MsgException.cpp
        ../MsgException.h
        ../session/ClientsClientInfo.cpp
        ../session/ClientsClientInfo.h
        ../session/ClientsClientInfoRepository.cpp
        ../session/ClientsClientInfoRepository.h
        ../packets/DisconnectPacket.cpp
        ../packets/DisconnectPacket.h
        mode/ConnectCLIModeHandler.cpp
        mode/ConnectCLIModeHandler.h
        mode/CLIModeHandler.h
        mode/CLIMode.h
        mode/CLIModeHandler.cpp
        ClientConnectionManager.cpp
        ClientConnectionManager.h
        mode/SubscribeCLIModeHandler.cpp
        mode/SubscribeCLIModeHandler.h
        ../packets/factories/SubscribePacketFactory.h
        ../packets/factories/SubscribePacketFactory.cpp
        ../packets/SubscribePacket.h
        ../packets/SubscribePacket.cpp
        ../packets/SubscribeAckPacket.cpp
        ../packets/SubscribeAckPacket.h
        ../handlers/SubscribeAckPacketHandler.cpp
        ../handlers/SubscribeAckPacketHandler.h
        ../packets/parsers/SubscribeAckPacketParser.cpp
        ../packets/parsers/SubscribeAckPacketParser.h
        ../packets/factories/UnsubAckPacketFactory.h
        ../packets/factories/UnsubAckPacketFactory.cpp
        ../packets/UnsubscribePacket.cpp ../packets/UnsubscribePacket.h
        ../packets/factories/UnsubscribePacketFactory.cpp
        ../packets/factories/UnsubscribePacketFactory.h
        ../packets/UnsubAckPacket.cpp
        ../packets/UnsubAckPacket.h
        ../packets/parsers/UnsubAckPacketParser.cpp
        ../packets/parsers/UnsubAckPacketParser.h
        ../handlers/UnsubAckPacketHandler.cpp
        ../handlers/UnsubAckPacketHandler.h
        mode/UnsubscribeCLIModeHandler.cpp
        mode/UnsubscribeCLIModeHandler.h
        mode/PublishCLIModeHandler.cpp
        mode/PublishCLIModeHandler.h
        ../packets/factories/PublishPacketFactory.cpp
        ../packets/factories/PublishPacketFactory.h
        ../packets/PublishPacket.cpp
        ../packets/PublishPacket.h
        ../packets/parsers/PublishPacketParser.cpp
        ../packets/parsers/PublishPacketParser.h
        ../handlers/ClientPublishPacketHandler.cpp
        ../handlers/ClientPublishPacketHandler.h
        ../Subscription.cpp
        ../Subscription.h
        ../handlers/ClientPublishPacketHandler.h
        ../handlers/ClientPublishPacketHandler.cpp
        ../topic/ServerTopicRepository.h
        ../topic/ServerTopicRepository.cpp
        ../topic/Topic.h
        ../topic/Topic.cpp
        ../topic/Message.h
        ../topic/Message.cpp)

# target_include_directories(lmqtt__client PRIVATE ../handlers ../io ../packets
# ../packet_factories)
