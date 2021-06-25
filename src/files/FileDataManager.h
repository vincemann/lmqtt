#ifndef __FILELOCATOR_H__
#define __FILELOCATOR_H__

#include <dirent.h>
#include <malloc.h>
#include <string.h>

class FileDataManager{

// combines with / in between to heap obj
static char* combinePaths(const char* s1,const char* s2){
    int len = strlen(s1) + strlen(s2) + 1;
    char* filePath = (char *) malloc(len);
    //    char filePath[len];
    sprintf(filePath,"%s/%s",s1,s2);
    return filePath;
}
public:
    char* find(const char* startDir, const char* name);
    int store(const char* targetDir,const char* name,const char* content);
};

#endif // __FILELOCATOR_H__