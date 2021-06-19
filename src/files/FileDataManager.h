#ifndef __FILELOCATOR_H__
#define __FILELOCATOR_H__

#include <dirent.h>

class FileDataManager{
public:
    char* find(char* startDir, char* name);
    int store(char* targetDir, char* name, char* content);
};

#endif // __FILELOCATOR_H__