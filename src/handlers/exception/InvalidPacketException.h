//
// Created by vince on 29.04.21.
//

#ifndef LMQTT__SERVER_INVALIDPACKETEXCEPTION_H
#define LMQTT__SERVER_INVALIDPACKETEXCEPTION_H

#include <exception>

class InvalidPacketException : public std::exception {
private:
    const char* _msg;
public:
    InvalidPacketException(const char* msg);
    const char * what () const throw ();
};


#endif //LMQTT__SERVER_INVALIDPACKETEXCEPTION_H
