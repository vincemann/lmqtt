//
// Created by vince on 08.04.21.
//

#include "Utils.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


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

bool Utils::isAlNum(const char * s){
    bool alnum = true;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (! isalnum((int)s[i])){
            alnum= false;
            break;
        }
    }
    return alnum;
}

void Utils::printChars(unsigned char *ptr, int size)
{
    unsigned char *p = ptr;
    int i;
    bool chars = false;
    for (i=0; i<size; i++) {
        if (isalnum(p[i])){
            chars=true;
            printf("%c", p[i]);
        } else{
            if (chars){
                printf("%s", " ");
            }
            printf("%02hhX ", p[i]);
            chars=false;
        }
    }
    printf("\n");
}




// always starts creating dirs from home
char* Utils::createHomeDirectoryChain(char* dirChain,bool del) {

    char *home = getenv("HOME");
    char *dir = (char *) malloc(strlen(home) + strlen(dirChain) + 1);
    strcpy(dir, home);
    char delim[] = "/";

    char *partialDir;

    /* get the first currDir */
//    partialDir = strtok(strdup(dirChain), delim);
//    partialDir = strtok(NULL, delim);

    /* walk through other tokens */
    int index = 0;
    while(1) {
        if (index == 0){
            partialDir = strtok(strdup(dirChain), delim);
            index = 1;
        } else{
            partialDir = strtok(NULL, delim);
        }
        if (partialDir == NULL){
            break;
        }
        printf("'%s'\n", partialDir);
        char *slash = "/";
        strcat(dir, slash);
        strcat(dir, partialDir);
        Utils::createDirectory(dir);
    }
    if(del){
        delete dir;
        return 0;
    }else{
        char* finalDir = Utils::smartstrcat(dir,"/");
        delete dir;
        return finalDir;
    }
}




//    int dirChainLen = -1;
//    for (const auto &item : *dirs){
//        dirChainLen += strlen(item);
//    }
////    const char* targetDir = "/.lmqtt/server/sessions";
//    char* home = getenv("HOME");
//    char* dir = (char*) malloc(strlen(home) + dirChainLen + 1);
//    strcpy(dir, home);
//
//    for (const auto &item : *dirs){
//        strcat(dir,item);
//        Utils::createDirectory(dir);
//    }
//}

char* Utils::toCharP(std::string* s){
    char *cstr = new char[s->length() + 1];
    strcpy(cstr, s->c_str());
    return cstr;
}

void Utils::printBytes(void *ptr, int size)
{
    unsigned char *p = (unsigned char *)ptr;
    int i;
    for (i=0; i<size; i++) {
        printf("%02hhX ", p[i]);
    }
    printf("\n");
}

void* Utils::vec_to_array(std::vector<void*> * vector)
{
    int i;
    void** array = (void **) malloc(sizeof(void *) * vector->size());
    for (i = 0; i < vector->size(); i++)
    {
        array[i] = vector->at(i);
    }

    return array;
}

//char* Utils::vec_to_deref_array(std::vector<char*> * vector)
//{
//    int i;
//    char* array = (char *) malloc(sizeof(char) * vector->size());
//    for (i = 0; i < vector->size(); i++)
//    {
//        char* p = (*vector)[i];
//        array[i] = e;
//    }
//
//    return array;
//}

void Utils::printBits(unsigned char val) {
    std::bitset<8> bits(val);
    std::cout << bits << '\n';
}

int Utils::createDirectory(const char* path){
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        int r = mkdir(path, 0700);
        return r;
    }else{
        printf("dir %s already exists\n", path);
        return 0;
    }
}

unsigned Utils::createBitMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}


void Utils::extractSubArray(unsigned char *srcArray, unsigned char *subArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        subArray[i] = srcArray[i];
    }
}

char *Utils::formatToCharP(const char *format,const char *arg) {
    char* r = new char;
    sprintf(r,format,arg);
    return r;
}

char *Utils::smartstrcat(const char *s1,const char *s2) {
    int dstStringLen = strlen(s1) + strlen(s2) + 1;
    char* dst = (char*) malloc(dstStringLen);
    memcpy(dst,"\0",1);
    strcat(dst,s1);
    strcat(dst,s2);
    return dst;
}

long Utils::lrand()
{
    if (sizeof(int) < sizeof(long))
        return (static_cast<long>(rand()) << (sizeof(int) * 8)) |
               rand();

    return rand();
}


