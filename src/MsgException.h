//
// Created by vince on 24.06.21.
//

#ifndef LMQTT__SERVER_MSGEXCEPTION_H
#define LMQTT__SERVER_MSGEXCEPTION_H

#include <exception>


class MsgException: public std::exception {
private:
    const char* _msg;
public:
    explicit MsgException(const char* msg);
    const char * what () const noexcept;
};


#endif //LMQTT__SERVER_MSGEXCEPTION_H
