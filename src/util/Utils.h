//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_UTILS_H
#define LMQTT__SERVER_UTILS_H


namespace Utils {
    unsigned char reverse_bits(unsigned char num);
    void printBits(unsigned char val);
    unsigned createBitMask(unsigned a, unsigned b);
    void extractSubArray(unsigned char *srcArray, unsigned char *subArray, int n);
    void printBytes(void *ptr, int size);
    void printChars(unsigned char *ptr, int size);
};


#endif //LMQTT__SERVER_UTILS_H
