//
// Created by vince on 25.04.21.
//

#include "Payload.h"


Payload::~Payload() {
    delete _data;
}

Payload::Payload(unsigned char *data, unsigned short size, bool prependSize=false) : _data(data), _dataSize(size),
                                                                                     prependSize(prependSize) {}

int Payload::getSize() const {
    int size = 0;
    if (prependSize){
        size += 2;
    }
    size += _dataSize;
    return size;
}

