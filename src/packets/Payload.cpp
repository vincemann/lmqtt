//
// Created by vince on 25.04.21.
//

#include "Payload.h"
#include <string.h>
#include <stdlib.h>


Payload::~Payload() {
    delete _data;
}

Payload::Payload(unsigned char *data, unsigned short size, bool prependSize) : _data(data), _dataSize(size),
                                                                                     _prependSize(prependSize) {}

int Payload::getSize() const {
    int size = 0;
    if (_prependSize){
        size += 2;
    }
    size += _dataSize;
    return size;
}


Payload::Payload(unsigned char data, unsigned short size) {
    unsigned char* pData = ( unsigned char*) malloc(size);
    // todo writes b4 7f instead of 00 b4
    memcpy(pData,&data,size);
    _data=pData;
    _dataSize = size;
    _prependSize=false;
}

