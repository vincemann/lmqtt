//
// Created by vince on 06.04.21.
//
#include <exception>

#ifndef LMQTT__SERVER_PARSEREXCEPTION_H
#define LMQTT__SERVER_PARSEREXCEPTION_H

class PacketParsingException : public std::exception{
private:
    const char* _msg;
public:
    PacketParsingException(const char* msg);
    const char * what () const throw ();
};

#endif //LMQTT__SERVER_PARSEREXCEPTION_H
