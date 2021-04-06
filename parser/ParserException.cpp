//
// Created by vince on 06.04.21.
//

#include "ParserException.h"

ParserException::ParserException(const char *msg) {
    m_msg=msg;
}

const char *ParserException::what() const throw() {
    return m_msg;
}
