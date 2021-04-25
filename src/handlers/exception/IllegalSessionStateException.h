//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
#define LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
#include <exception>

class IllegalSessionStateException : public std::exception {
private:
    const char* _msg;
public:
    IllegalSessionStateException(const char* msg);
    const char * what () const throw ();
};

#endif //LMQTT__SERVER_ILLEGALSESSIONSTATEEXCEPTION_H
