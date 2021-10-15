//
// Created by vince on 25.04.21.
//

#ifndef LMQTT__SERVER_PAYLOAD_H
#define LMQTT__SERVER_PAYLOAD_H


class Payload {
public:
    Payload(unsigned char *data, unsigned short size, bool prependSize=false);
    Payload(unsigned char data);
    Payload(unsigned short data);
    Payload(int data);
    unsigned char* _data;
    unsigned short _dataSize;
    bool _prependSize;

    int getSize() const;

    virtual ~Payload();
};


#endif //LMQTT__SERVER_PAYLOAD_H
