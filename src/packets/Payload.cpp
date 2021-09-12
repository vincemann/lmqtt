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

// for payloads that consist of only one byte
Payload::Payload(unsigned char data) {
    unsigned short size = sizeof(unsigned char);
    unsigned char* pData = ( unsigned char*) malloc(size);
    memcpy(pData,&data,size);
    _data=pData;
    _dataSize = size;
    _prependSize=false;
}

// for payloads that consist of only two byte
Payload::Payload(unsigned short data) {
    unsigned char* pData = ( unsigned char*) malloc(sizeof (unsigned short));
    pData[0]= data & 0xff;
    pData[1]= (data >> 8) & 0xff;
    _data=pData;
    _dataSize = sizeof (unsigned short);
    _prependSize=false;
}

Payload::Payload(unsigned long data) {
    unsigned char* pData = ( unsigned char*) malloc(sizeof (unsigned long));
    pData[0]= data & 0xff;
    pData[1]= (data >> 8) & 0xff;
    pData[2]= (data >> 16) & 0xff;
    pData[3]= (data >> 24) & 0xff;
    _data=pData;
    _dataSize = sizeof (unsigned long );
    _prependSize= false;
}


