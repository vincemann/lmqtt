//
// Created by vince on 06.04.21.
//


#ifndef LMQTT__SERVER_PARSEREXCEPTION_H
#define LMQTT__SERVER_PARSEREXCEPTION_H

#include <exception>

class PacketIOException : public std::exception{
private:
    const char* _msg;
public:
    PacketIOException(const char* msg);
    const char * what () const throw ();
};

#endif //LMQTT__SERVER_PARSEREXCEPTION_H
