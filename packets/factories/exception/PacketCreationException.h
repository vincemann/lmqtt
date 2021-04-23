//
// Created by vince on 08.04.21.
//


#ifndef LMQTT__SERVER_PACKETCREATIONEXCEPTION_H
#define LMQTT__SERVER_PACKETCREATIONEXCEPTION_H

#include <exception>


class PacketCreationException  : public std::exception {
private:
    const char* _msg;
public:
    PacketCreationException(const char* msg);
    const char * what () const throw ();
};

#endif //LMQTT__SERVER_PACKETCREATIONEXCEPTION_H
