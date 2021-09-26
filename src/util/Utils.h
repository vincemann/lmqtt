//
// Created by vince on 08.04.21.
//

#ifndef LMQTT__SERVER_UTILS_H
#define LMQTT__SERVER_UTILS_H
#include <string>
#include <vector>


namespace Utils {
    
    unsigned char reverse_bits(unsigned char num);
    void printBits(unsigned char val);
    unsigned createBitMask(unsigned a, unsigned b);
    void extractSubArray(unsigned char *srcArray, unsigned char *subArray, int n);
    void printBytes(void *ptr, int size);
    void printChars(unsigned char *ptr, int size);
    bool isAlNum(const char * s);
    char* toCharP(std::string* s);
    int createDirectory(const char* path);
    char* formatToCharP(const char* format,const char* arg);
    void* vec_to_array(std::vector<void*> * vector);
    char* vec_to_deref_array(std::vector<char*> * vector);
    char* createHomeDirectoryChain(char* dirChain,bool del=false);
    char* smartstrcat(const char* s1,const char* s2);
};


#endif //LMQTT__SERVER_UTILS_H
