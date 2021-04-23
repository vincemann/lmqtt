//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_UTILS_H
#define LMQTT__SERVER_UTILS_H


namespace Utils {
    unsigned char reverse_bits(unsigned char num);
    void print_bits(unsigned char val);
    unsigned create_bit_mask(unsigned a, unsigned b);
    void extractSubArray(char *srcArray, char *subArray, int n);
    char* remove_nullbytes_except_last(char* str, char find, char replace)
};


#endif //LMQTT__SERVER_UTILS_H
