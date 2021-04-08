//
// Created by vince on 08.04.21.
//

#include "Utils.h"
#include <iostream>
#include <bitset>


/* Function to reverse bits of num */
unsigned char Utils::reverse_bits(unsigned char num) {
    unsigned int NO_OF_BITS = 8;
    unsigned int reverse_num = 0, i, temp;

    for (i = 0; i < NO_OF_BITS; i++) {
        temp = (num & (1 << i));
        if (temp)
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }

    return reverse_num;
}

void Utils::print_bits(unsigned char val) {
    std::bitset<8> bits(val);
    std::cout << bits << '\n';
}

unsigned Utils::create_bit_mask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}
