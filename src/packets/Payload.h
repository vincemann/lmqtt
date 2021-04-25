//
// Created by vince on 25.04.21.
//

#ifndef LMQTT__SERVER_PAYLOAD_H
#define LMQTT__SERVER_PAYLOAD_H


class Payload {
public:
    Payload(unsigned char *data, unsigned short size, bool prependSize=false);

    unsigned char* _data;
    unsigned short _dataSize;
    bool prependSize;

    int getSize() const;

    virtual ~Payload();
};


#endif //LMQTT__SERVER_PAYLOAD_H
